#include "include/utils/DatabaseManager.h"
#include "include/utils/Logger.h"
#include <sstream>
#include <iostream>

DatabaseManager::DatabaseManager(const std::string &dbPath) : dbPath(dbPath), db(nullptr)
{
    connect();
}

DatabaseManager::~DatabaseManager()
{
    if (db)
    {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool DatabaseManager::connect()
{
    if (db)
    {
        return true; // Already connected
    }

    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc)
    {
        Logger::getInstance().error("Can't open database: " + std::string(sqlite3_errmsg(db)));
        sqlite3_close(db);
        db = nullptr;
        return false;
    }

    Logger::getInstance().info("Connected to database: " + dbPath);

    // Initialize tables if they don't exist
    if (!initializeTables())
    {
        Logger::getInstance().error("Failed to initialize database tables");
        sqlite3_close(db);
        db = nullptr;
        return false;
    }

    return true;
}

bool DatabaseManager::isConnected() const
{
    return db != nullptr;
}

bool DatabaseManager::reconnect()
{
    if (db)
    {
        sqlite3_close(db);
        db = nullptr;
    }
    return connect();
}

bool DatabaseManager::executeQuery(const std::string &query)
{
    if (!isConnected())
    {
        Logger::getInstance().error("Database not connected");
        return false;
    }

    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK)
    {
        std::string error = "SQL error: " + std::string(errMsg);
        Logger::getInstance().error(error);
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}

std::vector<std::map<std::string, std::string>> DatabaseManager::getRows(const std::string &query)
{
    std::vector<std::map<std::string, std::string>> results;

    if (!isConnected())
    {
        Logger::getInstance().error("Database not connected");
        return results;
    }

    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK)
    {
        Logger::getInstance().error("Failed to prepare statement: " + std::string(sqlite3_errmsg(db)));
        return results;
    }

    int colCount = sqlite3_column_count(stmt);

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        std::map<std::string, std::string> row;

        for (int i = 0; i < colCount; i++)
        {
            std::string colName = sqlite3_column_name(stmt, i);

            // Handle different column types
            if (sqlite3_column_type(stmt, i) == SQLITE_NULL)
            {
                row[colName] = "";
            }
            else
            {
                const unsigned char *textValue = sqlite3_column_text(stmt, i);
                if (textValue)
                {
                    row[colName] = reinterpret_cast<const char *>(textValue);
                }
                else
                {
                    row[colName] = "";
                }
            }
        }

        results.push_back(row);
    }

    if (rc != SQLITE_DONE)
    {
        Logger::getInstance().error("Error executing query: " + std::string(sqlite3_errmsg(db)));
    }

    sqlite3_finalize(stmt);
    return results;
}

std::string DatabaseManager::escapeString(const std::string &str)
{
    std::string result;
    result.reserve(str.length() * 2);

    for (char c : str)
    {
        if (c == '\'')
        {
            // Escape single quotes with another single quote (SQL standard)
            result += "''";
        }
        else
        {
            result += c;
        }
    }

    return result;
}

bool DatabaseManager::initializeTables()
{
    // Create clients table
    std::string clientsTable =
        "CREATE TABLE IF NOT EXISTS clients ("
        "client_id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "first_name TEXT NOT NULL, "
        "last_name TEXT NOT NULL, "
        "email TEXT UNIQUE NOT NULL, "
        "phone TEXT, "
        "company TEXT, "
        "position TEXT, "
        "registration_date TEXT, "
        "sessions_completed INTEGER DEFAULT 0, "
        "last_session_date TEXT, "
        "budget REAL DEFAULT 0.0"
        ")";

    if (!executeQuery(clientsTable))
    {
        return false;
    }

    // Create client_ai_models table for many-to-many relationship
    std::string clientAIModelsTable =
        "CREATE TABLE IF NOT EXISTS client_ai_models ("
        "client_id INTEGER, "
        "ai_model TEXT, "
        "PRIMARY KEY (client_id, ai_model), "
        "FOREIGN KEY (client_id) REFERENCES clients(client_id) ON DELETE CASCADE"
        ")";

    if (!executeQuery(clientAIModelsTable))
    {
        return false;
    }

    // Create client_proficiencies table
    std::string clientProficienciesTable =
        "CREATE TABLE IF NOT EXISTS client_proficiencies ("
        "client_id INTEGER, "
        "ai_model TEXT, "
        "level INTEGER, "
        "PRIMARY KEY (client_id, ai_model), "
        "FOREIGN KEY (client_id) REFERENCES clients(client_id) ON DELETE CASCADE"
        ")";

    if (!executeQuery(clientProficienciesTable))
    {
        return false;
    }

    // Create client_learning_goals table
    std::string clientGoalsTable =
        "CREATE TABLE IF NOT EXISTS client_learning_goals ("
        "client_id INTEGER, "
        "goal TEXT, "
        "PRIMARY KEY (client_id, goal), "
        "FOREIGN KEY (client_id) REFERENCES clients(client_id) ON DELETE CASCADE"
        ")";

    if (!executeQuery(clientGoalsTable))
    {
        return false;
    }

    // Create tutors table
    std::string tutorsTable =
        "CREATE TABLE IF NOT EXISTS tutors ("
        "user_id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT UNIQUE NOT NULL, "
        "password TEXT NOT NULL, "
        "first_name TEXT NOT NULL, "
        "last_name TEXT NOT NULL, "
        "email TEXT UNIQUE NOT NULL, "
        "phone TEXT, "
        "qualification TEXT, "
        "experience_years INTEGER DEFAULT 0, "
        "hourly_rate REAL DEFAULT 0.0, "
        "sessions_completed INTEGER DEFAULT 0, "
        "average_rating REAL DEFAULT 0.0"
        ")";

    if (!executeQuery(tutorsTable))
    {
        return false;
    }

    // Create tutor_specializations table
    std::string tutorSpecializationsTable =
        "CREATE TABLE IF NOT EXISTS tutor_specializations ("
        "tutor_id INTEGER, "
        "ai_model TEXT, "
        "PRIMARY KEY (tutor_id, ai_model), "
        "FOREIGN KEY (tutor_id) REFERENCES tutors(user_id) ON DELETE CASCADE"
        ")";

    if (!executeQuery(tutorSpecializationsTable))
    {
        return false;
    }

    // Create tutor_expertise table
    std::string tutorExpertiseTable =
        "CREATE TABLE IF NOT EXISTS tutor_expertise ("
        "tutor_id INTEGER, "
        "domain TEXT, "
        "PRIMARY KEY (tutor_id, domain), "
        "FOREIGN KEY (tutor_id) REFERENCES tutors(user_id) ON DELETE CASCADE"
        ")";

    if (!executeQuery(tutorExpertiseTable))
    {
        return false;
    }

    // Create tutor_ai_experience table
    std::string tutorAIExperienceTable =
        "CREATE TABLE IF NOT EXISTS tutor_ai_experience ("
        "tutor_id INTEGER, "
        "ai_model TEXT, "
        "level INTEGER, "
        "PRIMARY KEY (tutor_id, ai_model), "
        "FOREIGN KEY (tutor_id) REFERENCES tutors(user_id) ON DELETE CASCADE"
        ")";

    if (!executeQuery(tutorAIExperienceTable))
    {
        return false;
    }

    // Create ai_models table
    std::string aiModelsTable =
        "CREATE TABLE IF NOT EXISTS ai_models ("
        "model_id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT UNIQUE NOT NULL, "
        "version TEXT, "
        "developer TEXT, "
        "category TEXT, "
        "release_date TEXT, "
        "description TEXT, "
        "complexity_level INTEGER DEFAULT 1, "
        "popularity_rank INTEGER DEFAULT 0, "
        "tutors_available INTEGER DEFAULT 0, "
        "documentation_url TEXT, "
        "is_deprecated INTEGER DEFAULT 0"
        ")";

    if (!executeQuery(aiModelsTable))
    {
        return false;
    }

    // Create ai_model_capabilities table
    std::string aiModelCapabilitiesTable =
        "CREATE TABLE IF NOT EXISTS ai_model_capabilities ("
        "model_id INTEGER, "
        "capability TEXT, "
        "PRIMARY KEY (model_id, capability), "
        "FOREIGN KEY (model_id) REFERENCES ai_models(model_id) ON DELETE CASCADE"
        ")";

    if (!executeQuery(aiModelCapabilitiesTable))
    {
        return false;
    }

    // Create ai_model_limitations table
    std::string aiModelLimitationsTable =
        "CREATE TABLE IF NOT EXISTS ai_model_limitations ("
        "model_id INTEGER, "
        "limitation TEXT, "
        "PRIMARY KEY (model_id, limitation), "
        "FOREIGN KEY (model_id) REFERENCES ai_models(model_id) ON DELETE CASCADE"
        ")";

    if (!executeQuery(aiModelLimitationsTable))
    {
        return false;
    }

    // Create ai_model_use_cases table
    std::string aiModelUseCasesTable =
        "CREATE TABLE IF NOT EXISTS ai_model_use_cases ("
        "model_id INTEGER, "
        "use_case TEXT, "
        "PRIMARY KEY (model_id, use_case), "
        "FOREIGN KEY (model_id) REFERENCES ai_models(model_id) ON DELETE CASCADE"
        ")";

    if (!executeQuery(aiModelUseCasesTable))
    {
        return false;
    }

    // Create ai_model_parameters table
    std::string aiModelParametersTable =
        "CREATE TABLE IF NOT EXISTS ai_model_parameters ("
        "model_id INTEGER, "
        "param_name TEXT, "
        "param_description TEXT, "
        "PRIMARY KEY (model_id, param_name), "
        "FOREIGN KEY (model_id) REFERENCES ai_models(model_id) ON DELETE CASCADE"
        ")";

    if (!executeQuery(aiModelParametersTable))
    {
        return false;
    }

    // Create learning_materials table
    std::string learningMaterialsTable =
        "CREATE TABLE IF NOT EXISTS learning_materials ("
        "material_id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "title TEXT NOT NULL, "
        "description TEXT, "
        "type TEXT, "
        "format TEXT, "
        "author TEXT, "
        "creation_date TEXT, "
        "difficulty_level INTEGER DEFAULT 1, "
        "url TEXT, "
        "local_path TEXT, "
        "estimated_time_minutes INTEGER DEFAULT 0, "
        "rating REAL DEFAULT 0.0, "
        "usage_count INTEGER DEFAULT 0"
        ")";

    if (!executeQuery(learningMaterialsTable))
    {
        return false;
    }

    // Create material_ai_models table
    std::string materialAIModelsTable =
        "CREATE TABLE IF NOT EXISTS material_ai_models ("
        "material_id INTEGER, "
        "model_id INTEGER, "
        "PRIMARY KEY (material_id, model_id), "
        "FOREIGN KEY (material_id) REFERENCES learning_materials(material_id) ON DELETE CASCADE, "
        "FOREIGN KEY (model_id) REFERENCES ai_models(model_id) ON DELETE CASCADE"
        ")";

    if (!executeQuery(materialAIModelsTable))
    {
        return false;
    }

    // Create material_tags table
    std::string materialTagsTable =
        "CREATE TABLE IF NOT EXISTS material_tags ("
        "material_id INTEGER, "
        "tag TEXT, "
        "PRIMARY KEY (material_id, tag), "
        "FOREIGN KEY (material_id) REFERENCES learning_materials(material_id) ON DELETE CASCADE"
        ")";

    if (!executeQuery(materialTagsTable))
    {
        return false;
    }

    // Create tutoring_sessions table
    std::string tutoringSessionsTable =
        "CREATE TABLE IF NOT EXISTS tutoring_sessions ("
        "session_id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "client_id INTEGER, "
        "tutor_id INTEGER, "
        "session_date TEXT, "
        "start_time TEXT, "
        "duration_minutes INTEGER, "
        "status TEXT DEFAULT 'Scheduled', "
        "client_rating REAL DEFAULT 0.0, "
        "learning_objectives TEXT, "
        "session_notes TEXT, "
        "skills_gained TEXT, "
        "homework_assigned TEXT, "
        "session_cost REAL DEFAULT 0.0, "
        "payment_status TEXT DEFAULT 'Pending', "
        "is_remote INTEGER DEFAULT 1, "
        "platform TEXT, "
        "FOREIGN KEY (client_id) REFERENCES clients(client_id), "
        "FOREIGN KEY (tutor_id) REFERENCES tutors(user_id)"
        ")";

    if (!executeQuery(tutoringSessionsTable))
    {
        return false;
    }

    // Create session_ai_models table
    std::string sessionAIModelsTable =
        "CREATE TABLE IF NOT EXISTS session_ai_models ("
        "session_id INTEGER, "
        "model_id INTEGER, "
        "PRIMARY KEY (session_id, model_id), "
        "FOREIGN KEY (session_id) REFERENCES tutoring_sessions(session_id) ON DELETE CASCADE, "
        "FOREIGN KEY (model_id) REFERENCES ai_models(model_id) ON DELETE CASCADE"
        ")";

    if (!executeQuery(sessionAIModelsTable))
    {
        return false;
    }

    // Create session_topics table
    std::string sessionTopicsTable =
        "CREATE TABLE IF NOT EXISTS session_topics ("
        "session_id INTEGER, "
        "topic TEXT, "
        "PRIMARY KEY (session_id, topic), "
        "FOREIGN KEY (session_id) REFERENCES tutoring_sessions(session_id) ON DELETE CASCADE"
        ")";

    if (!executeQuery(sessionTopicsTable))
    {
        return false;
    }

    // Create administrators table
    std::string adminsTable =
        "CREATE TABLE IF NOT EXISTS administrators ("
        "user_id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT UNIQUE NOT NULL, "
        "password TEXT NOT NULL, "
        "first_name TEXT NOT NULL, "
        "last_name TEXT NOT NULL, "
        "email TEXT UNIQUE NOT NULL, "
        "phone TEXT, "
        "access_level TEXT DEFAULT 'Limited', "
        "can_manage_ai INTEGER DEFAULT 0, "
        "can_manage_users INTEGER DEFAULT 0, "
        "last_login TEXT"
        ")";

    if (!executeQuery(adminsTable))
    {
        return false;
    }

    // Add default admin if none exists
    std::string checkAdmin = "SELECT COUNT(*) as count FROM administrators";
    auto results = getRows(checkAdmin);

    if (!results.empty() && results[0]["count"] == "0")
    {
        std::string addAdmin =
            "INSERT INTO administrators (username, password, first_name, last_name, email, "
            "access_level, can_manage_ai, can_manage_users) VALUES "
            "('admin', 'admin123', 'Admin', 'User', 'admin@example.com', "
            "'Full', 1, 1)";

        if (!executeQuery(addAdmin))
        {
            return false;
        }

        Logger::getInstance().info("Created default admin user");
    }

    return true;
}