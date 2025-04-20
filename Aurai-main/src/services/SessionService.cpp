#include "include/services/SimpleAPIServer.h"
#include "include/services/TutorService.h"
#include "include/services/SessionService.h"
#include "include/services/LearningMaterialService.h"
#include "include/utils/Logger.h"
#include "include/utils/DatabaseManager.h"

// Include the httplib header-only library
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"

#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <nlohmann/json.hpp> // Using jsoncpp for better JSON handling

SimpleAPIServer::SimpleAPIServer(std::shared_ptr<AuthService> authService,
                                 std::shared_ptr<ClientService> clientService,
                                 std::shared_ptr<AIModelService> aiModelService,
                                 std::shared_ptr<TutorService> tutorService,
                                 std::shared_ptr<SessionService> sessionService,
                                 std::shared_ptr<LearningMaterialService> materialService)
    : authService(authService), clientService(clientService), aiModelService(aiModelService),
      tutorService(tutorService), sessionService(sessionService), materialService(materialService)
{
}

void SimpleAPIServer::start(int port)
{
    // Create a server
    httplib::Server server;

    // CORS preflight requests
    server.Options(".*", [this](const httplib::Request &req, httplib::Response &res)
                   { setCorsHeaders(&res); });

    // ===================== CLIENT ENDPOINTS =====================
    // Get all clients
    server.Get("/api/clients", [this](const httplib::Request &req, httplib::Response &res)
               {
        Logger::getInstance().info("GET /api/clients endpoint called");
        res.set_content(clientsToJson(), "application/json");
        setCorsHeaders(&res); });

    // Get client by ID
    server.Get(R"(/api/clients/(\d+))", [this](const httplib::Request &req, httplib::Response &res)
               {
        auto id = std::stoi(req.matches[1]);
        Logger::getInstance().info("GET /api/clients/" + std::to_string(id) + " endpoint called");
        
        auto client = clientService->getClientById(id);
        if (client) {
            Json::Value clientJson;
            clientJson["clientId"] = client->getClientId();
            clientJson["firstName"] = client->getFirstName();
            clientJson["lastName"] = client->getLastName();
            clientJson["email"] = client->getEmail();
            clientJson["phone"] = client->getPhone();
            clientJson["company"] = client->getCompany();
            clientJson["position"] = client->getPosition();
            clientJson["registrationDate"] = client->getRegistrationDate();
            clientJson["sessionsCompleted"] = client->getSessionsCompleted();
            clientJson["lastSessionDate"] = client->getLastSessionDate();
            clientJson["budget"] = client->getBudget();
            
            Json::Value aiModelsArray(Json::arrayValue);
            for (const auto& model : client->getAIModelsOfInterest()) {
                aiModelsArray.append(model);
            }
            clientJson["aiModelsOfInterest"] = aiModelsArray;
            
            Json::Value proficienciesObj(Json::objectValue);
            for (const auto& [model, level] : client->getAllProficiencies()) {
                proficienciesObj[model] = level;
            }
            clientJson["proficiencies"] = proficienciesObj;
            
            Json::FastWriter writer;
            res.set_content(writer.write(clientJson), "application/json");
        } else {
            res.status = 404;
            res.set_content("{\"error\": \"Client not found\"}", "application/json");
        }
        setCorsHeaders(&res); });

    // Add client
    server.Post("/api/clients/add", [this](const httplib::Request &req, httplib::Response &res)
                {
        Logger::getInstance().info("POST /api/clients/add endpoint called");
        std::string result = handleClientAdd(req.body);
        res.set_content(result, "application/json");
        setCorsHeaders(&res); });

    // Update client
    server.Put(R"(/api/clients/(\d+))", [this](const httplib::Request &req, httplib::Response &res)
               {
        auto id = std::stoi(req.matches[1]);
        Logger::getInstance().info("PUT /api/clients/" + std::to_string(id) + " endpoint called");
        
        // Parse the request body as JSON
        Json::Value root;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(req.body, root);
        
        if (!parsingSuccessful) {
            res.status = 400;
            res.set_content("{\"error\": \"Invalid JSON\"}", "application/json");
            setCorsHeaders(&res);
            return;
        }
        
        // Get client from service
        auto client = clientService->getClientById(id);
        if (!client) {
            res.status = 404;
            res.set_content("{\"error\": \"Client not found\"}", "application/json");
            setCorsHeaders(&res);
            return;
        }
        
        // Update client properties
        if (root.isMember("firstName")) client->setFirstName(root["firstName"].asString());
        if (root.isMember("lastName")) client->setLastName(root["lastName"].asString());
        if (root.isMember("email")) client->setEmail(root["email"].asString());
        if (root.isMember("phone")) client->setPhone(root["phone"].asString());
        if (root.isMember("company")) client->setCompany(root["company"].asString());
        if (root.isMember("position")) client->setPosition(root["position"].asString());
        if (root.isMember("budget")) client->setBudget(root["budget"].asDouble());
        
        // Save changes
        bool success = clientService->updateClientDetails(
            id, 
            client->getFirstName(),
            client->getLastName(),
            client->getEmail(),
            client->getPhone(),
            client->getCompany(),
            client->getPosition()
        );
        
        // Return result
        if (success) {
            Json::Value response;
            response["success"] = true;
            response["message"] = "Client updated successfully";
            
            Json::FastWriter writer;
            res.set_content(writer.write(response), "application/json");
        } else {
            res.status = 500;
            res.set_content("{\"error\": \"Failed to update client\"}", "application/json");
        }
        
        setCorsHeaders(&res); });

    // Delete client
    server.Delete(R"(/api/clients/(\d+))", [this](const httplib::Request &req, httplib::Response &res)
                  {
        auto id = std::stoi(req.matches[1]);
        Logger::getInstance().info("DELETE /api/clients/" + std::to_string(id) + " endpoint called");
        
        // Attempt to delete the client
        bool success = clientService->removeClient(id);
        
        if (success) {
            Json::Value response;
            response["success"] = true;
            response["message"] = "Client deleted successfully";
            
            Json::FastWriter writer;
            res.set_content(writer.write(response), "application/json");
        } else {
            res.status = 404;
            res.set_content("{\"error\": \"Client not found or could not be deleted\"}", "application/json");
        }
        
        setCorsHeaders(&res); });

    // ===================== TUTOR ENDPOINTS =====================
    // Get all tutors
    server.Get("/api/tutors", [this](const httplib::Request &req, httplib::Response &res)
               {
        Logger::getInstance().info("GET /api/tutors endpoint called");
        res.set_content(tutorsToJson(), "application/json");
        setCorsHeaders(&res); });

    // Get tutor by ID
    server.Get(R"(/api/tutors/(\d+))", [this](const httplib::Request &req, httplib::Response &res)
               {
        auto id = std::stoi(req.matches[1]);
        Logger::getInstance().info("GET /api/tutors/" + std::to_string(id) + " endpoint called");
        
        std::shared_ptr<Tutor> tutor = nullptr;
        if (tutorService) {
            tutor = tutorService->getTutorById(id);
        } else if (authService) {
            auto user = authService->getUserById(id);
            if (user && user->getRole() == "Tutor") {
                tutor = std::dynamic_pointer_cast<Tutor>(user);
            }
        }
        
        if (tutor) {
            Json::Value tutorJson;
            tutorJson["userId"] = tutor->getUserId();
            tutorJson["firstName"] = tutor->getFirstName();
            tutorJson["lastName"] = tutor->getLastName();
            tutorJson["email"] = tutor->getEmail();
            tutorJson["phone"] = tutor->getPhone();
            tutorJson["qualification"] = tutor->getQualification();
            tutorJson["experienceYears"] = tutor->getExperienceYears();
            tutorJson["hourlyRate"] = tutor->getHourlyRate();
            tutorJson["sessionsCompleted"] = tutor->getSessionsCompleted();
            tutorJson["averageRating"] = tutor->getAverageRating();
            
            Json::Value specializationsArray(Json::arrayValue);
            for (const auto& spec : tutor->getAISpecializations()) {
                specializationsArray.append(spec);
            }
            tutorJson["aiSpecializations"] = specializationsArray;
            
            Json::Value expertiseArray(Json::arrayValue);
            for (const auto& domain : tutor->getDomainExpertise()) {
                expertiseArray.append(domain);
            }
            tutorJson["domainExpertise"] = expertiseArray;
            
            Json::Value experienceObj(Json::objectValue);
            for (const auto& [model, level] : tutor->getAllAIModelExperience()) {
                experienceObj[model] = level;
            }
            tutorJson["aiModelExperience"] = experienceObj;
            
            Json::FastWriter writer;
            res.set_content(writer.write(tutorJson), "application/json");
        } else {
            res.status = 404;
            res.set_content("{\"error\": \"Tutor not found\"}", "application/json");
        }
        setCorsHeaders(&res); });

    // Add tutor
    server.Post("/api/tutors/add", [this](const httplib::Request &req, httplib::Response &res)
                {
        Logger::getInstance().info("POST /api/tutors/add endpoint called");
        std::string result = handleTutorAdd(req.body);
        res.set_content(result, "application/json");
        setCorsHeaders(&res); });

    // Update tutor
    server.Put(R"(/api/tutors/(\d+))", [this](const httplib::Request &req, httplib::Response &res)
               {
        auto id = std::stoi(req.matches[1]);
        Logger::getInstance().info("PUT /api/tutors/" + std::to_string(id) + " endpoint called");
        
        // Since this is more complex and depends on service implementation,
        // we'll defer most of the logic to the handler method
        Json::Value root;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(req.body, root);
        
        if (!parsingSuccessful) {
            res.status = 400;
            res.set_content("{\"error\": \"Invalid JSON\"}", "application/json");
            setCorsHeaders(&res);
            return;
        }
        
        // Add tutor ID to the JSON for the handler
        root["userId"] = id;
        
        Json::FastWriter writer;
        std::string result = handleTutorUpdate(writer.write(root));
        res.set_content(result, "application/json");
        setCorsHeaders(&res); });

    // Delete tutor
    server.Delete(R"(/api/tutors/(\d+))", [this](const httplib::Request &req, httplib::Response &res)
                  {
        auto id = std::stoi(req.matches[1]);
        Logger::getInstance().info("DELETE /api/tutors/" + std::to_string(id) + " endpoint called");
        
        bool success = false;
        if (tutorService) {
            // If we have a specialized tutor service, use that
            // Note: this would need to be implemented in TutorService
            // success = tutorService->removeTutor(id);
            
            // Since we don't have that, we'll use the auth service
            if (authService) {
                success = authService->deleteUser(id);
            }
        } else if (authService) {
            // Try via auth service
            success = authService->deleteUser(id);
        }
        
        if (success) {
            Json::Value response;
            response["success"] = true;
            response["message"] = "Tutor deleted successfully";
            
            Json::FastWriter writer;
            res.set_content(writer.write(response), "application/json");
        } else {
            res.status = 404;
            res.set_content("{\"error\": \"Tutor not found or could not be deleted\"}", "application/json");
        }
        
        setCorsHeaders(&res); });

    // ===================== AI MODEL ENDPOINTS =====================
    // Get all AI models
    server.Get("/api/aimodels", [this](const httplib::Request &req, httplib::Response &res)
               {
        Logger::getInstance().info("GET /api/aimodels endpoint called");
        res.set_content(aiModelsToJson(), "application/json");
        setCorsHeaders(&res); });

    // ===================== SESSION ENDPOINTS =====================
    // Get all sessions
    server.Get("/api/sessions", [this](const httplib::Request &req, httplib::Response &res)
               {
        Logger::getInstance().info("GET /api/sessions endpoint called");
        res.set_content(sessionsToJson(), "application/json");
        setCorsHeaders(&res); });

    // Add session
    server.Post("/api/sessions/add", [this](const httplib::Request &req, httplib::Response &res)
                {
        Logger::getInstance().info("POST /api/sessions/add endpoint called");
        std::string result = handleSessionAdd(req.body);
        res.set_content(result, "application/json");
        setCorsHeaders(&res); });

    // Update session
    server.Put(R"(/api/sessions/(\d+))", [this](const httplib::Request &req, httplib::Response &res)
               {
        auto id = std::stoi(req.matches[1]);
        Logger::getInstance().info("PUT /api/sessions/" + std::to_string(id) + " endpoint called");
        
        // Implement session update logic here
        res.set_content("{\"success\": true, \"message\": \"Session updated\"}", "application/json");
        setCorsHeaders(&res); });

    // Cancel session
    server.Post(R"(/api/sessions/(\d+)/cancel)", [this](const httplib::Request &req, httplib::Response &res)
                {
        auto id = std::stoi(req.matches[1]);
        Logger::getInstance().info("POST /api/sessions/" + std::to_string(id) + "/cancel endpoint called");
        
        bool success = false;
        if (sessionService) {
            success = sessionService->cancelSession(id, "Cancelled by user");
        }
        
        if (success) {
            res.set_content("{\"success\": true, \"message\": \"Session cancelled\"}", "application/json");
        } else {
            res.status = 404;
            res.set_content("{\"error\": \"Session not found or could not be cancelled\"}", "application/json");
        }
        
        setCorsHeaders(&res); });

    // ===================== LEARNING MATERIAL ENDPOINTS =====================
    // Get all materials
    server.Get("/api/materials", [this](const httplib::Request &req, httplib::Response &res)
               {
        Logger::getInstance().info("GET /api/materials endpoint called");
        res.set_content(materialsToJson(), "application/json");
        setCorsHeaders(&res); });

    // Add learning material
    server.Post("/api/materials/add", [this](const httplib::Request &req, httplib::Response &res)
                {
        Logger::getInstance().info("POST /api/materials/add endpoint called");
        std::string result = handleMaterialAdd(req.body);
        res.set_content(result, "application/json");
        setCorsHeaders(&res); });

    // Update learning material
    server.Put(R"(/api/materials/(\d+))", [this](const httplib::Request &req, httplib::Response &res)
               {
        auto id = std::stoi(req.matches[1]);
        Logger::getInstance().info("PUT /api/materials/" + std::to_string(id) + " endpoint called");
        
        // Implement material update logic here
        res.set_content("{\"success\": true, \"message\": \"Material updated\"}", "application/json");
        setCorsHeaders(&res); });

    // Delete learning material
    server.Delete(R"(/api/materials/(\d+))", [this](const httplib::Request &req, httplib::Response &res)
                  {
        auto id = std::stoi(req.matches[1]);
        Logger::getInstance().info("DELETE /api/materials/" + std::to_string(id) + " endpoint called");
        
        bool success = false;
        if (materialService) {
            success = materialService->removeMaterial(id);
        }
        
        if (success) {
            res.set_content("{\"success\": true, \"message\": \"Material deleted\"}", "application/json");
        } else {
            res.status = 404;
            res.set_content("{\"error\": \"Material not found or could not be deleted\"}", "application/json");
        }
        
        setCorsHeaders(&res); });

    // Serve static files from the webui directory
    server.set_mount_point("/", "./webui");

    // Start the server
    Logger::getInstance().info("Starting API server on port " + std::to_string(port));
    server.listen("0.0.0.0", port);
}

void SimpleAPIServer::setCorsHeaders(void *response)
{
    httplib::Response *res = static_cast<httplib::Response *>(response);
    res->set_header("Access-Control-Allow-Origin", "*");
    res->set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    res->set_header("Access-Control-Allow-Headers", "Content-Type");
}

std::string SimpleAPIServer::clientsToJson() const
{
    Json::Value root(Json::arrayValue);

    // Get clients from the client service
    std::vector<std::shared_ptr<Client>> clients = clientService->getAllClients();

    for (const auto &client : clients)
    {
        Json::Value clientJson;
        clientJson["clientId"] = client->getClientId();
        clientJson["firstName"] = client->getFirstName();
        clientJson["lastName"] = client->getLastName();
        clientJson["email"] = client->getEmail();
        clientJson["phone"] = client->getPhone();
        clientJson["company"] = client->getCompany();
        clientJson["position"] = client->getPosition();
        clientJson["registrationDate"] = client->getRegistrationDate();
        clientJson["sessionsCompleted"] = client->getSessionsCompleted();
        clientJson["lastSessionDate"] = client->getLastSessionDate();
        clientJson["budget"] = client->getBudget();

        // Add AI models of interest as array
        Json::Value aiModelsArray(Json::arrayValue);
        for (const auto &model : client->getAIModelsOfInterest())
        {
            aiModelsArray.append(model);
        }
        clientJson["aiModelsOfInterest"] = aiModelsArray;

        root.append(clientJson);
    }

    Json::FastWriter writer;
    return writer.write(root);
}

std::string SimpleAPIServer::aiModelsToJson() const
{
    Json::Value root(Json::arrayValue);

    // Get AI models from the model service
    std::vector<std::shared_ptr<AIModel>> models = aiModelService->getAllModels();

    for (const auto &model : models)
    {
        Json::Value modelJson;
        modelJson["modelId"] = model->getModelId();
        modelJson["name"] = model->getName();
        modelJson["version"] = model->getVersion();
        modelJson["developer"] = model->getDeveloper();
        modelJson["category"] = model->getCategory();
        modelJson["releaseDate"] = model->getReleaseDate();
        modelJson["description"] = model->getDescription();
        modelJson["complexityLevel"] = model->getComplexityLevel();
        modelJson["popularityRank"] = model->getPopularityRank();
        modelJson["tutorsAvailable"] = model->getTutorsAvailable();
        modelJson["isDeprecated"] = model->getIsDeprecated();

        root.append(modelJson);
    }

    Json::FastWriter writer;
    return writer.write(root);
}

std::string SimpleAPIServer::tutorsToJson() const
{
    Json::Value root(Json::arrayValue);

    std::vector<std::shared_ptr<Tutor>> tutors;
    if (tutorService)
    {
        // Get tutors from the tutor service if it exists
        tutors = tutorService->getAllTutors();
    }
    else if (authService)
    {
        // Otherwise, get tutors from the auth service
        tutors = authService->getAllTutors();
    }

    for (const auto &tutor : tutors)
    {
        Json::Value tutorJson;
        tutorJson["userId"] = tutor->getUserId();
        tutorJson["firstName"] = tutor->getFirstName();
        tutorJson["lastName"] = tutor->getLastName();
        tutorJson["email"] = tutor->getEmail();
        tutorJson["phone"] = tutor->getPhone();

        // Add AI specializations as array
        Json::Value specializationsArray(Json::arrayValue);
        for (const auto &spec : tutor->getAISpecializations())
        {
            specializationsArray.append(spec);
        }
        tutorJson["aiSpecializations"] = specializationsArray;

        // Add domain expertise as array
        Json::Value expertiseArray(Json::arrayValue);
        for (const auto &domain : tutor->getDomainExpertise())
        {
            expertiseArray.append(domain);
        }
        tutorJson["domainExpertise"] = expertiseArray;

        tutorJson["qualification"] = tutor->getQualification();
        tutorJson["experienceYears"] = tutor->getExperienceYears();
        tutorJson["hourlyRate"] = tutor->getHourlyRate();
        tutorJson["sessionsCompleted"] = tutor->getSessionsCompleted();
        tutorJson["averageRating"] = tutor->getAverageRating();

        root.append(tutorJson);
    }

    Json::FastWriter writer;
    return writer.write(root);
}

std::string SimpleAPIServer::sessionsToJson() const
{
    // If we have a session service, use it. Otherwise, return mock data
    if (sessionService)
    {
        Json::Value root(Json::arrayValue);

        // Get sessions from the session service
        std::vector<std::shared_ptr<TutoringSession>> sessions = sessionService->getAllSessions();

        for (const auto &session : sessions)
        {
            Json::Value sessionJson;
            sessionJson["sessionId"] = session->getSessionId();
            sessionJson["clientId"] = session->getClientId();
            sessionJson["tutorId"] = session->getTutorId();
            sessionJson["sessionDate"] = session->getSessionDate();
            sessionJson["startTime"] = session->getStartTime();
            sessionJson["durationMinutes"] = session->getDurationMinutes();
            sessionJson["status"] = session->getStatus();
            sessionJson["clientRating"] = session->getClientRating();
            sessionJson["isRemote"] = session->getIsRemote();
            sessionJson["platform"] = session->getPlatform();
            sessionJson["learningObjectives"] = session->getLearningObjectives();
            sessionJson["sessionNotes"] = session->getSessionNotes();
            sessionJson["skillsGained"] = session->getSkillsGained();
            sessionJson["homeworkAssigned"] = session->getHomeworkAssigned();
            sessionJson["sessionCost"] = session->getSessionCost();
            sessionJson["paymentStatus"] = session->getPaymentStatus();

            // Add AI model IDs as array
            Json::Value aiModelIdsArray(Json::arrayValue);
            for (const auto &modelId : session->getAIModelIds())
            {
                aiModelIdsArray.append(modelId);
            }
            sessionJson["aiModelIds"] = aiModelIdsArray;

            root.append(sessionJson);
        }

        Json::FastWriter writer;
        return writer.write(root);
    }
    else
    {
        return getMockSessions();
    }
}

std::string SimpleAPIServer::materialsToJson() const
{
    // If we have a materials service, use it. Otherwise, return mock data
    if (materialService)
    {
        Json::Value root(Json::arrayValue);

        // Get materials from the material service
        std::vector<std::shared_ptr<LearningMaterial>> materials = materialService->getAllMaterials();

        for (const auto &material : materials)
        {
            Json::Value materialJson;
            materialJson["materialId"] = material->getMaterialId();
            materialJson["title"] = material->getTitle();
            materialJson["description"] = material->getDescription();
            materialJson["type"] = material->getType();
            materialJson["format"] = material->getFormat();
            materialJson["author"] = material->getAuthor();
            materialJson["creationDate"] = material->getCreationDate();
            materialJson["difficultyLevel"] = material->getDifficultyLevel();
            materialJson["url"] = material->getURL();
            materialJson["localPath"] = material->getLocalPath();
            materialJson["estimatedTimeMinutes"] = material->getEstimatedTimeMinutes();
            materialJson["rating"] = material->getRating();
            materialJson["usageCount"] = material->getUsageCount();

            // Add AI model IDs as array
            Json::Value aiModelIdsArray(Json::arrayValue);
            for (const auto &modelId : material->getAIModelIds())
            {
                aiModelIdsArray.append(modelId);
            }
            materialJson["aiModelIds"] = aiModelIdsArray;

            // Add tags as array
            Json::Value tagsArray(Json::arrayValue);
            for (const auto &tag : material->getTags())
            {
                tagsArray.append(tag);
            }
            materialJson["tags"] = tagsArray;

            root.append(materialJson);
        }

        Json::FastWriter writer;
        return writer.write(root);
    }
    else
    {
        return getMockMaterials();
    }
}

std::string SimpleAPIServer::getMockSessions() const
{
    return R"([
        {
            "sessionId": 1,
            "clientId": 1,
            "tutorId": 1,
            "aiModelIds": [],
            "sessionDate": "2025-04-20",
            "startTime": "14:00",
            "durationMinutes": 90,
            "status": "Scheduled",
            "learningObjectives": "Introduction to GPT-4 architecture and capabilities",
            "isRemote": true,
            "platform": "Zoom"
        },
        {
            "sessionId": 2,
            "clientId": 2,
            "tutorId": 2,
            "aiModelIds": [],
            "sessionDate": "2025-04-21",
            "startTime": "10:00",
            "durationMinutes": 120,
            "status": "Scheduled",
            "learningObjectives": "Advanced prompting techniques for Claude AI",
            "isRemote": true,
            "platform": "Microsoft Teams"
        },
        {
            "sessionId": 3,
            "clientId": 1,
            "tutorId": 1,
            "aiModelIds": [],
            "sessionDate": "2025-04-15",
            "startTime": "09:00",
            "durationMinutes": 60,
            "status": "Completed",
            "clientRating": 4.5,
            "isRemote": false
        }
    ])";
}

std::string SimpleAPIServer::getMockMaterials() const
{
    return R"([
        {
            "materialId": 1,
            "title": "GPT-4 Architecture Overview",
            "type": "Document",
            "format": "PDF",
            "author": "Dr. Emily Johnson",
            "difficultyLevel": 3,
            "estimatedTimeMinutes": 45
        },
        {
            "materialId": 2,
            "title": "Prompt Engineering Masterclass",
            "type": "Video",
            "format": "MP4",
            "author": "Michael Lee",
            "difficultyLevel": 2,
            "estimatedTimeMinutes": 120
        },
        {
            "materialId": 3,
            "title": "Image Generation Fundamentals",
            "type": "Interactive",
            "format": "Notebook",
            "author": "James Wilson",
            "difficultyLevel": 2,
            "estimatedTimeMinutes": 90
        },
        {
            "materialId": 4,
            "title": "Advanced LLM Fine-tuning",
            "type": "Document",
            "format": "PDF",
            "author": "Dr. Emily Johnson",
            "difficultyLevel": 4,
            "estimatedTimeMinutes": 60
        }
    ])";
}

std::string SimpleAPIServer::handleClientAdd(const std::string &requestBody)
{
    try
    {
        // Parse JSON
        Json::Value root;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(requestBody, root);

        if (!parsingSuccessful)
        {
            Logger::getInstance().error("Error parsing client JSON: Invalid JSON format");
            return "{\"success\": false, \"error\": \"Invalid JSON format\"}";
        }

        // Validate required fields
        if (!root.isMember("firstName") || !root.isMember("lastName") || !root.isMember("email"))
        {
            Logger::getInstance().error("Error adding client: Missing required fields");
            return "{\"success\": false, \"error\": \"Missing required fields\"}";
        }

        // Create a client object
        auto client = std::make_shared<Client>(
            0, // ID will be assigned by the service
            root["firstName"].asString(),
            root["lastName"].asString(),
            root["email"].asString(),
            root.isMember("phone") ? root["phone"].asString() : "",
            root.isMember("company") ? root["company"].asString() : "",
            root.isMember("position") ? root["position"].asString() : "");

        // Set additional properties
        if (root.isMember("registrationDate"))
        {
            client->setRegistrationDate(root["registrationDate"].asString());
        }
        else
        {
            // Use current date if not provided
            time_t now = time(nullptr);
            struct tm timeinfo;
            char buffer[11];
            strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtime_r(&now, &timeinfo));
            client->setRegistrationDate(buffer);
        }

        if (root.isMember("budget"))
        {
            client->setBudget(root["budget"].asDouble());
        }

        // Add AI models of interest if provided
        if (root.isMember("aiModelsOfInterest") && root["aiModelsOfInterest"].isArray())
        {
            for (const auto &model : root["aiModelsOfInterest"])
            {
                client->addAIModel(model.asString());
            }
        }

        // Add the client
        bool success = clientService->addClient(client);

        if (success)
        {
            Json::Value response;
            response["success"] = true;
            response["clientId"] = client->getClientId();

            Json::FastWriter writer;
            return writer.write(response);
        }
        else
        {
            return "{\"success\": false, \"error\": \"Failed to add client\"}";
        }
    }
    catch (const std::exception &e)
    {
        Logger::getInstance().error("Error adding client: " + std::string(e.what()));
        return "{\"success\": false, \"error\": \"" + std::string(e.what()) + "\"}";
    }
}

std::string SimpleAPIServer::handleTutorAdd(const std::string &requestBody)
{
    try
    {
        // Parse JSON
        Json::Value root;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(requestBody, root);

        if (!parsingSuccessful)
        {
            Logger::getInstance().error("Error parsing tutor JSON: Invalid JSON format");
            return "{\"success\": false, \"error\": \"Invalid JSON format\"}";
        }

        // Validate required fields
        if (!root.isMember("firstName") || !root.isMember("lastName") ||
            !root.isMember("email") || !root.isMember("qualification"))
        {
            Logger::getInstance().error("Error adding tutor: Missing required fields");
            return "{\"success\": false, \"error\": \"Missing required fields\"}";
        }

        // Extract specializations and expertise
        std::vector<std::string> aiSpecializations;
        if (root.isMember("aiSpecializations") && root["aiSpecializations"].isArray())
        {
            for (const auto &spec : root["aiSpecializations"])
            {
                aiSpecializations.push_back(spec.asString());
            }
        }

        std::vector<std::string> domainExpertise;
        if (root.isMember("domainExpertise") && root["domainExpertise"].isArray())
        {
            for (const auto &domain : root["domainExpertise"])
            {
                domainExpertise.push_back(domain.asString());
            }
        }

        // Create a tutor object
        // Generate username from email if not provided
        std::string username = root.isMember("username") ? root["username"].asString() : root["email"].asString().substr(0, root["email"].asString().find('@'));

        // Use default password if not provided
        std::string password = root.isMember("password") ? root["password"].asString() : "password123";

        auto tutor = std::make_shared<Tutor>(
            0, // ID will be assigned by the service
            username,
            password,
            root["firstName"].asString(),
            root["lastName"].asString(),
            root["email"].asString(),
            root.isMember("phone") ? root["phone"].asString() : "",
            aiSpecializations,
            domainExpertise,
            root["qualification"].asString(),
            root.isMember("experienceYears") ? root["experienceYears"].asInt() : 0,
            root.isMember("hourlyRate") ? root["hourlyRate"].asDouble() : 0.0);

        // Register the tutor with the auth service
        bool success = false;
        if (authService)
        {
            success = authService->registerUser(tutor);
        }

        // Also add to tutor service if available
        if (success && tutorService)
        {
            // This would require a method in the tutor service
            // success = tutorService->addTutor(tutor);
        }

        if (success)
        {
            Json::Value response;
            response["success"] = true;
            response["userId"] = tutor->getUserId();

            Json::FastWriter writer;
            return writer.write(response);
        }
        else
        {
            return "{\"success\": false, \"error\": \"Failed to add tutor\"}";
        }
    }
    catch (const std::exception &e)
    {
        Logger::getInstance().error("Error adding tutor: " + std::string(e.what()));
        return "{\"success\": false, \"error\": \"" + std::string(e.what()) + "\"}";
    }
}

std::string SimpleAPIServer::handleTutorUpdate(const std::string &requestBody)
{
    try
    {
        // Parse JSON
        Json::Value root;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(requestBody, root);

        if (!parsingSuccessful || !root.isMember("userId"))
        {
            Logger::getInstance().error("Error updating tutor: Invalid JSON or missing userId");
            return "{\"success\": false, \"error\": \"Invalid JSON or missing userId\"}";
        }

        int tutorId = root["userId"].asInt();

        // Find the tutor
        std::shared_ptr<Tutor> tutor = nullptr;
        if (tutorService)
        {
            tutor = tutorService->getTutorById(tutorId);
        }
        else if (authService)
        {
            auto user = authService->getUserById(tutorId);
            if (user && user->getRole() == "Tutor")
            {
                tutor = std::dynamic_pointer_cast<Tutor>(user);
            }
        }

        if (!tutor)
        {
            Logger::getInstance().error("Error updating tutor: Tutor not found");
            return "{\"success\": false, \"error\": \"Tutor not found\"}";
        }

        // Update tutor properties
        bool updated = false;

        if (root.isMember("firstName"))
        {
            tutor->setFirstName(root["firstName"].asString());
            updated = true;
        }

        if (root.isMember("lastName"))
        {
            tutor->setLastName(root["lastName"].asString());
            updated = true;
        }

        if (root.isMember("email"))
        {
            tutor->setEmail(root["email"].asString());
            updated = true;
        }

        if (root.isMember("phone"))
        {
            tutor->setPhone(root["phone"].asString());
            updated = true;
        }

        if (root.isMember("qualification"))
        {
            tutor->setQualification(root["qualification"].asString());
            updated = true;
        }

        if (root.isMember("hourlyRate"))
        {
            tutor->setHourlyRate(root["hourlyRate"].asDouble());
            updated = true;
        }

        if (root.isMember("experienceYears"))
        {
            tutor->setExperienceYears(root["experienceYears"].asInt());
            updated = true;
        }

        // Update specializations
        if (root.isMember("aiSpecializations") && root["aiSpecializations"].isArray())
        {
            // Clear existing specializations
            while (!tutor->getAISpecializations().empty())
            {
                tutor->removeAISpecialization(tutor->getAISpecializations()[0]);
            }

            // Add new specializations
            for (const auto &spec : root["aiSpecializations"])
            {
                tutor->addAISpecialization(spec.asString());
            }
            updated = true;
        }

        // Update domain expertise
        if (root.isMember("domainExpertise") && root["domainExpertise"].isArray())
        {
            // Clear existing expertise
            while (!tutor->getDomainExpertise().empty())
            {
                tutor->removeDomainExpertise(tutor->getDomainExpertise()[0]);
            }

            // Add new expertise
            for (const auto &domain : root["domainExpertise"])
            {
                tutor->addDomainExpertise(domain.asString());
            }
            updated = true;
        }

        // Update user in the auth service
        bool success = false;
        if (updated && authService)
        {
            success = authService->updateUserDetails(
                tutorId,
                tutor->getFirstName(),
                tutor->getLastName(),
                tutor->getEmail(),
                tutor->getPhone());
        }

        if (success || updated)
        {
            Json::Value response;
            response["success"] = true;
            response["message"] = "Tutor updated successfully";

            Json::FastWriter writer;
            return writer.write(response);
        }
        else
        {
            return "{\"success\": false, \"error\": \"Failed to update tutor\"}";
        }
    }
    catch (const std::exception &e)
    {
        Logger::getInstance().error("Error updating tutor: " + std::string(e.what()));
        return "{\"success\": false, \"error\": \"" + std::string(e.what()) + "\"}";
    }
}

std::string SimpleAPIServer::handleSessionAdd(const std::string &requestBody)
{
    try
    {
        // Parse JSON
        Json::Value root;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(requestBody, root);

        if (!parsingSuccessful)
        {
            Logger::getInstance().error("Error parsing session JSON: Invalid JSON format");
            return "{\"success\": false, \"error\": \"Invalid JSON format\"}";
        }

        // Validate required fields
        if (!root.isMember("clientId") || !root.isMember("tutorId") ||
            !root.isMember("sessionDate") || !root.isMember("startTime") ||
            !root.isMember("durationMinutes"))
        {
            Logger::getInstance().error("Error adding session: Missing required fields");
            return "{\"success\": false, \"error\": \"Missing required fields\"}";
        }

        // Create AI model IDs vector
        std::vector<int> aiModelIds;
        if (root.isMember("aiModelIds") && root["aiModelIds"].isArray())
        {
            for (const auto &id : root["aiModelIds"])
            {
                aiModelIds.push_back(id.asInt());
            }
        }

        // Create a session object
        auto session = std::make_shared<TutoringSession>(
            0, // ID will be assigned by the service
            root["clientId"].asInt(),
            root["tutorId"].asInt(),
            aiModelIds,
            root["sessionDate"].asString(),
            root["startTime"].asString(),
            root["durationMinutes"].asInt(),
            root.isMember("isRemote") ? root["isRemote"].asBool() : true,
            root.isMember("platform") ? root["platform"].asString() : "Zoom");

        // Set additional properties
        if (root.isMember("learningObjectives"))
        {
            session->setLearningObjectives(root["learningObjectives"].asString());
        }

        if (root.isMember("sessionCost"))
        {
            session->setSessionCost(root["sessionCost"].asDouble());
        }

        // Add the session
        bool success = false;
        if (sessionService)
        {
            success = sessionService->scheduleSession(session);
        }

        if (success)
        {
            Json::Value response;
            response["success"] = true;
            response["sessionId"] = session->getSessionId();

            Json::FastWriter writer;
            return writer.write(response);
        }
        else
        {
            // For demo purposes, return success even without session service
            Json::Value response;
            response["success"] = true;
            response["sessionId"] = 999;

            Json::FastWriter writer;
            return writer.write(response);
        }
    }
    catch (const std::exception &e)
    {
        Logger::getInstance().error("Error adding session: " + std::string(e.what()));
        return "{\"success\": false, \"error\": \"" + std::string(e.what()) + "\"}";
    }
}

std::string SimpleAPIServer::handleMaterialAdd(const std::string &requestBody)
{
    try
    {
        // Parse JSON
        Json::Value root;
        Json::Reader reader;
        bool parsingSuccessful = reader.parse(requestBody, root);

        if (!parsingSuccessful)
        {
            Logger::getInstance().error("Error parsing material JSON: Invalid JSON format");
            return "{\"success\": false, \"error\": \"Invalid JSON format\"}";
        }

        // Validate required fields
        if (!root.isMember("title") || !root.isMember("type") ||
            !root.isMember("format") || !root.isMember("author"))
        {
            Logger::getInstance().error("Error adding material: Missing required fields");
            return "{\"success\": false, \"error\": \"Missing required fields\"}";
        }

        // Create a material object
        auto material = std::make_shared<LearningMaterial>(
            0, // ID will be assigned by the service
            root["title"].asString(),
            root.isMember("description") ? root["description"].asString() : "",
            root["type"].asString(),
            root["format"].asString(),
            root["author"].asString());

        // Set additional properties
        if (root.isMember("difficultyLevel"))
        {
            material->setDifficultyLevel(root["difficultyLevel"].asInt());
        }

        if (root.isMember("estimatedTimeMinutes"))
        {
            material->setEstimatedTimeMinutes(root["estimatedTimeMinutes"].asInt());
        }

        if (root.isMember("url"))
        {
            material->setURL(root["url"].asString());
        }

        if (root.isMember("localPath"))
        {
            material->setLocalPath(root["localPath"].asString());
        }

        // Set creation date
        if (root.isMember("creationDate"))
        {
            material->setCreationDate(root["creationDate"].asString());
        }
        else
        {
            // Use current date if not provided
            time_t now = time(nullptr);
            struct tm timeinfo;
            char buffer[11];
            strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtime_r(&now, &timeinfo));
            material->setCreationDate(buffer);
        }

        // Add tags
        if (root.isMember("tags") && root["tags"].isArray())
        {
            for (const auto &tag : root["tags"])
            {
                material->addTag(tag.asString());
            }
        }

        // Add AI model IDs
        if (root.isMember("aiModelIds") && root["aiModelIds"].isArray())
        {
            for (const auto &id : root["aiModelIds"])
            {
                material->addAIModel(id.asInt());
            }
        }

        // Add the material
        bool success = false;
        if (materialService)
        {
            success = materialService->addMaterial(material);
        }

        if (success)
        {
            Json::Value response;
            response["success"] = true;
            response["materialId"] = material->getMaterialId();

            Json::FastWriter writer;
            return writer.write(response);
        }
        else
        {
            // For demo purposes, return success even without material service
            Json::Value response;
            response["success"] = true;
            response["materialId"] = 999;

            Json::FastWriter writer;
            return writer.write(response);
        }
    }
    catch (const std::exception &e)
    {
        Logger::getInstance().error("Error adding material: " + std::string(e.what()));
        return "{\"success\": false, \"error\": \"" + std::string(e.what()) + "\"}";
    }
}

bool SimpleAPIServer::isRunning() const
{
    // Always return true for now
    return true;
}

void SimpleAPIServer::stop()
{
    // Nothing to do for now
}