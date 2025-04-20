// include/utils/DatabaseManager.h
#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <sqlite3.h>
#include <mutex>

class DatabaseManager
{
private:
    sqlite3 *db;
    std::string dbPath;
    std::mutex dbMutex;
    bool connected;

    void ensureConnected();

public:
    DatabaseManager(const std::string &dbPath);
    ~DatabaseManager();

    // Connection management
    bool connect();
    bool disconnect();
    bool isConnected() const;
    bool reconnect();

    // Basic database operations
    bool executeQuery(const std::string &query);
    std::vector<std::map<std::string, std::string>> getRows(const std::string &query);
    int getLastInsertId();

    // Utility functions
    std::string escapeString(const std::string &input);
    bool checkTableExists(const std::string &tableName);
    void initializeDatabase();

    // Transaction management
    bool beginTransaction();
    bool commitTransaction();
    bool rollbackTransaction();

    // Prepared statements
    std::shared_ptr<sqlite3_stmt> prepareStatement(const std::string &sql);
    bool executePrepared(std::shared_ptr<sqlite3_stmt> stmt);
    std::vector<std::map<std::string, std::string>> getRowsPrepared(std::shared_ptr<sqlite3_stmt> stmt);

    // Error handling
    std::string getLastError() const;
};

#endif // DATABASE_MANAGER_H