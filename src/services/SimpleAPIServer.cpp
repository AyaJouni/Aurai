#include "include/services/SimpleAPIServer.h"
#include "include/services/TutorService.h"
#include "include/services/AIModelService.h"
#include "include/services/AuthService.h"
#include "include/services/SessionService.h"
#include "include/services/LearningMaterialService.h"
#include "include/services/ClientService.h"
#include "include/models/AIModel.h"
#include "include/models/Tutor.h"
#include "include/models/TutoringSession.h"
#include "include/models/LearningMaterial.h"
#include "include/models/Client.h"
#include "include/utils/Logger.h"
#include <nlohmann/json.hpp>

// Include the httplib header-only library
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"

#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using json = nlohmann::json;

std::string SimpleAPIServer::handleClientAdd(const std::string &requestBody)
{
    try
    {
        nlohmann::json jsonData = nlohmann::json::parse(requestBody);

        // Validate required fields and type correctness
        std::vector<std::string> requiredFields = {"firstName", "lastName", "email"};
        for (const auto &field : requiredFields)
        {
            if (!jsonData.contains(field) || !jsonData[field].is_string())
            {
                return nlohmann::json{
                    {"status", "error"},
                    {"message", "Missing or invalid field: " + field}}
                    .dump();
            }
        }

        // Create and populate Client object
        auto newClient = std::make_shared<Client>();
        newClient->setFirstName(jsonData["firstName"]);
        newClient->setLastName(jsonData["lastName"]);
        newClient->setEmail(jsonData["email"]);

        if (jsonData.contains("phone") && jsonData["phone"].is_string())
        {
            newClient->setPhone(jsonData["phone"]);
        }
        if (jsonData.contains("company") && jsonData["company"].is_string())
        {
            newClient->setCompany(jsonData["company"]);
        }
        if (jsonData.contains("position") && jsonData["position"].is_string())
        {
            newClient->setPosition(jsonData["position"]);
        }
        if (jsonData.contains("budget") && jsonData["budget"].is_number())
        {
            newClient->setBudget(jsonData["budget"]);
        }

        if (jsonData.contains("aiModelsOfInterest") && jsonData["aiModelsOfInterest"].is_array())
        {
            for (const auto &model : jsonData["aiModelsOfInterest"])
            {
                if (model.is_string())
                {
                    newClient->addAIModel(model);
                }
            }
        }

        if (jsonData.contains("learningGoals") && jsonData["learningGoals"].is_array())
        {
            for (const auto &goal : jsonData["learningGoals"])
            {
                if (goal.is_string())
                {
                    newClient->addLearningGoal(goal);
                }
            }
        }

        if (jsonData.contains("proficiencies") && jsonData["proficiencies"].is_object())
        {
            for (const auto &[model, level] : jsonData["proficiencies"].items())
            {
                if (level.is_number_integer())
                {
                    newClient->setAIModelProficiency(model, level.get<int>());
                }
            }
        }

        // Add client using the service instance
        ClientService clientService;
        bool success = clientService.addClient(newClient);

        if (success)
        {
            return nlohmann::json{
                {"status", "success"},
                {"message", "Client added successfully"}}
                .dump();
        }
        else
        {
            return nlohmann::json{
                {"status", "error"},
                {"message", "Failed to add client"}}
                .dump();
        }
    }
    catch (const std::exception &e)
    {
        return nlohmann::json{
            {"status", "error"},
            {"message", std::string("Exception: ") + e.what()}}
            .dump();
    }
}

std::string SimpleAPIServer::handleTutorAdd(const std::string &requestBody)
{
    try
    {
        nlohmann::json jsonData = nlohmann::json::parse(requestBody);

        // Validate required fields
        std::vector<std::string> requiredFields = {
            "username", "password", "firstName", "lastName",
            "email", "qualification", "experienceYears", "hourlyRate"};
        for (const auto &field : requiredFields)
        {
            if (!jsonData.contains(field))
            {
                return nlohmann::json{
                    {"status", "error"},
                    {"message", "Missing required field: " + field}}
                    .dump();
            }
        }

        // Create a new Tutor
        auto newTutor = std::make_shared<Tutor>(
            0, // userId will be set by service
            jsonData["username"],
            jsonData["password"],
            jsonData["firstName"],
            jsonData["lastName"],
            jsonData["email"],
            jsonData.value("phone", ""),
            jsonData.value("aiSpecializations", std::vector<std::string>{}),
            jsonData.value("domainExpertise", std::vector<std::string>{}),
            jsonData["qualification"],
            jsonData["experienceYears"],
            jsonData["hourlyRate"]);

        // Use AuthService to register the tutor
        bool success = authService->registerUser(newTutor);

        if (success)
        {
            return nlohmann::json{
                {"status", "success"},
                {"message", "Tutor added successfully"},
                {"tutorId", newTutor->getUserId()}}
                .dump();
        }
        else
        {
            return nlohmann::json{
                {"status", "error"},
                {"message", "Failed to add tutor"}}
                .dump();
        }
    }
    catch (const std::exception &e)
    {
        return nlohmann::json{
            {"status", "error"},
            {"message", std::string("Exception: ") + e.what()}}
            .dump();
    }
}

std::string SimpleAPIServer::handleTutorUpdate(const std::string &requestBody)
{
    try
    {
        nlohmann::json jsonData = nlohmann::json::parse(requestBody);

        // Validate user ID
        if (!jsonData.contains("userId"))
        {
            return nlohmann::json{
                {"status", "error"},
                {"message", "Missing tutor ID"}}
                .dump();
        }

        int tutorId = jsonData["userId"];

        // Use AuthService to find the user
        auto user = authService->getUserByUsername(jsonData["username"]);
        if (!user)
        {
            return nlohmann::json{
                {"status", "error"},
                {"message", "Tutor not found"}}
                .dump();
        }

        // Update user details
        bool detailsUpdated = authService->updateUserDetails(
            tutorId,
            jsonData.value("firstName", user->getFirstName()),
            jsonData.value("lastName", user->getLastName()),
            jsonData.value("email", user->getEmail()),
            jsonData.value("phone", user->getPhone()));

        return nlohmann::json{
            {"status", "success"},
            {"message", "Tutor updated successfully"}}
            .dump();
    }
    catch (const std::exception &e)
    {
        return nlohmann::json{
            {"status", "error"},
            {"message", std::string("Exception: ") + e.what()}}
            .dump();
    }
}

std::string SimpleAPIServer::handleTutorDelete(const std::string &requestBody)
{
    try
    {
        nlohmann::json jsonData = nlohmann::json::parse(requestBody);

        // Validate user ID
        if (!jsonData.contains("userId"))
        {
            return nlohmann::json{
                {"status", "error"},
                {"message", "Missing tutor ID"}}
                .dump();
        }

        int tutorId = jsonData["userId"];

        // Use AuthService to delete the user
        bool success = authService->deleteUser(tutorId);

        if (success)
        {
            return nlohmann::json{
                {"status", "success"},
                {"message", "Tutor deleted successfully"}}
                .dump();
        }
        else
        {
            return nlohmann::json{
                {"status", "error"},
                {"message", "Failed to delete tutor"}}
                .dump();
        }
    }
    catch (const std::exception &e)
    {
        return nlohmann::json{
            {"status", "error"},
            {"message", std::string("Exception: ") + e.what()}}
            .dump();
    }
}

SimpleAPIServer::SimpleAPIServer(std::shared_ptr<AuthService> authService,
                                 std::shared_ptr<ClientService> clientService,
                                 std::shared_ptr<AIModelService> aiModelService,
                                 std::shared_ptr<TutorService> tutorService,
                                 std::shared_ptr<SessionService> sessionService,
                                 std::shared_ptr<LearningMaterialService> materialService)
    : authService(authService), clientService(clientService), aiModelService(aiModelService),
      tutorService(tutorService), sessionService(sessionService), materialService(materialService)
{
    Logger::getInstance().info("SimpleAPIServer initialized without database");
}

void SimpleAPIServer::start(int port)
{
    // Create a server
    httplib::Server server;

    // CORS preflight requests
    server.Options(".*", [this](const httplib::Request &, httplib::Response &res)
                   { setCorsHeaders(&res); });

    // ===================== CLIENT ENDPOINTS =====================
    // Get all clients
    server.Get("/api/clients", [this](const httplib::Request &, httplib::Response &res)
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
            json clientJson;
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
            
            json aiModelsArray = json::array();
            for (const auto& model : client->getAIModelsOfInterest()) {
                aiModelsArray.push_back(model);
            }
            clientJson["aiModelsOfInterest"] = aiModelsArray;
            
            json proficienciesObj = json::object();
            for (const auto& [model, level] : client->getAllProficiencies()) {
                proficienciesObj[model] = level;
            }
            clientJson["proficiencies"] = proficienciesObj;
            
            res.set_content(clientJson.dump(), "application/json");
        } else {
            res.status = 404;
            res.set_content("{\"error\": \"Client not found\"}", "application/json");
        }
        setCorsHeaders(&res); });

    // Add client
    server.Post("/api/clients/add", [this](const httplib::Request &req, httplib::Response &res)
                {
        Logger::getInstance().info("POST /api/clients/add endpoint called with body: " + req.body);
        std::string result = handleClientAdd(req.body);
        Logger::getInstance().info("Add client result: " + result);
        res.set_content(result, "application/json");
        setCorsHeaders(&res); });

    // In SimpleAPIServer or a specific ClientController
    server.Post("/api/clients/search", [this](const httplib::Request &req, httplib::Response &res)
                {
        try {
            // Parse JSON body
            json searchData = json::parse(req.body);
            std::string query = searchData["query"];
            std::string searchType = searchData["searchType"];

            // Perform search using your ClientService
            std::vector<std::shared_ptr<Client>> results;
            if (searchType == "name") {
                results = clientService->searchClientsByName(query);
            } else if (searchType == "email") {
                results = clientService->searchClientsByEmail(query);
            } else if (searchType == "company") {
                results = clientService->searchClientsByCompany(query);
            }

            // Convert results to JSON and send
            json responseJson = json::array();
            for (const auto& client : results) {
                // Convert client to JSON
                json clientJson;
                // Map client properties
                responseJson.push_back(clientJson);
            }

            res.set_content(responseJson.dump(), "application/json");
        } catch (const std::exception& e) {
            // Error handling
            res.status = 400;
            res.set_content("{\"error\": \"Search failed\"}", "application/json");
        } });

    // Update client
    server.Put(R"(/api/clients/(\d+))", [this](const httplib::Request &req, httplib::Response &res)
               {
        auto id = std::stoi(req.matches[1]);
        Logger::getInstance().info("PUT /api/clients/" + std::to_string(id) + " endpoint called");
        
        // Parse the request body as JSON
        try {
            json root = json::parse(req.body);
            
            // Get client from service
            auto client = clientService->getClientById(id);
            if (!client) {
                res.status = 404;
                res.set_content("{\"error\": \"Client not found\"}", "application/json");
                setCorsHeaders(&res);
                return;
            }
            
            // Update client properties
            if (root.contains("firstName")) client->setFirstName(root["firstName"]);
            if (root.contains("lastName")) client->setLastName(root["lastName"]);
            if (root.contains("email")) client->setEmail(root["email"]);
            if (root.contains("phone")) client->setPhone(root["phone"]);
            if (root.contains("company")) client->setCompany(root["company"]);
            if (root.contains("position")) client->setPosition(root["position"]);
            if (root.contains("budget")) client->setBudget(root["budget"]);
            
            // Update AI models of interest if provided
            if (root.contains("aiModelsOfInterest") && root["aiModelsOfInterest"].is_array()) {
                // Clear existing models first
                auto currentModels = client->getAIModelsOfInterest();
                for (const auto& model : currentModels) {
                    client->removeAIModel(model);
                }
                
                // Add new models
                for (const auto& model : root["aiModelsOfInterest"]) {
                    client->addAIModel(model);
                }
            }
            
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
                json response;
                response["success"] = true;
                response["message"] = "Client updated successfully";
                
                res.set_content(response.dump(), "application/json");
            } else {
                res.status = 500;
                res.set_content("{\"error\": \"Failed to update client\"}", "application/json");
            }
        } catch (const json::exception& e) {
            res.status = 400;
            res.set_content("{\"error\": \"Invalid JSON: " + std::string(e.what()) + "\"}", "application/json");
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
            json response;
            response["success"] = true;
            response["message"] = "Client deleted successfully";
            
            res.set_content(response.dump(), "application/json");
        } else {
            res.status = 404;
            res.set_content("{\"error\": \"Client not found or could not be deleted\"}", "application/json");
        }
        
        setCorsHeaders(&res); });

    // ===================== TUTOR ENDPOINTS =====================
    // Get all tutors
    server.Get("/api/tutors", [this](const httplib::Request &, httplib::Response &res)
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
            json tutorJson;
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
            tutorJson["username"] = tutor->getUsername();
            
            json specializationsArray = json::array();
            for (const auto& spec : tutor->getAISpecializations()) {
                specializationsArray.push_back(spec);
            }
            tutorJson["aiSpecializations"] = specializationsArray;
            
            json expertiseArray = json::array();
            for (const auto& domain : tutor->getDomainExpertise()) {
                expertiseArray.push_back(domain);
            }
            tutorJson["domainExpertise"] = expertiseArray;
            
            json experienceObj = json::object();
            for (const auto& [model, level] : tutor->getAllAIModelExperience()) {
                experienceObj[model] = level;
            }
            tutorJson["aiModelExperience"] = experienceObj;
            
            res.set_content(tutorJson.dump(), "application/json");
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

    server.Post("/api/tutors/search", [this](const httplib::Request &req, httplib::Response &res)
                {
        try {
            json searchData = json::parse(req.body);
            std::string query = searchData["query"];
            std::string searchType = searchData["searchType"];

            std::vector<std::shared_ptr<Tutor>> results;
            if (searchType == "name") {
                results = tutorService->searchTutorsByName(query);
            } else if (searchType == "email") {
                results = tutorService->searchTutorsByEmail(query);
            } else if (searchType == "specialization") {
                results = tutorService->searchTutorsBySpecialization(query);
            }

            json responseJson = json::array();
            for (const auto& tutor : results) {
                json tutorJson;
                tutorJson["firstName"] = tutor->getFirstName();
                tutorJson["lastName"] = tutor->getLastName();
                tutorJson["email"] = tutor->getEmail();
                tutorJson["phone"] = tutor->getPhone();
                tutorJson["experienceYears"] = tutor->getExperienceYears();
                tutorJson["hourlyRate"] = tutor->getHourlyRate();
                tutorJson["userId"] = tutor->getUserId();
                tutorJson["aiSpecializations"] = tutor->getAiSpecializations(); // this should be a std::vector
                tutorJson["domainExpertise"] = tutor->getDomainExpertise();     // this should be a std::vector
                responseJson.push_back(tutorJson);
            }

            res.set_content(responseJson.dump(), "application/json");
        } catch (const std::exception& e) {
            res.status = 400;
            res.set_content("{\"error\": \"Search failed\"}", "application/json");
        } });

    // Update tutor
    server.Put(R"(/api/tutors/(\d+))", [this](const httplib::Request &req, httplib::Response &res)
               {
        auto id = std::stoi(req.matches[1]);
        Logger::getInstance().info("PUT /api/tutors/" + std::to_string(id) + " endpoint called");
        
        // Parse the request body as JSON
        try {
            json root = json::parse(req.body);
            
            // Add tutor ID to the JSON for the handler
            root["userId"] = id;
            
            std::string result = handleTutorUpdate(root.dump());
            res.set_content(result, "application/json");
        } catch (const json::exception& e) {
            res.status = 400;
            res.set_content("{\"error\": \"Invalid JSON: " + std::string(e.what()) + "\"}", "application/json");
        }
        
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
            json response;
            response["success"] = true;
            response["message"] = "Tutor deleted successfully";
            
            res.set_content(response.dump(), "application/json");
        } else {
            res.status = 404;
            res.set_content("{\"error\": \"Tutor not found or could not be deleted\"}", "application/json");
        }
        
        setCorsHeaders(&res); });

    // ===================== AI MODEL ENDPOINTS =====================
    // Get all AI models
    server.Get("/api/aimodels", [this](const httplib::Request &, httplib::Response &res)
               {
        Logger::getInstance().info("GET /api/aimodels endpoint called");
        res.set_content(aiModelsToJson(), "application/json");
        setCorsHeaders(&res); });

    // ===================== SESSION ENDPOINTS =====================
    // Get all sessions
    server.Get("/api/sessions", [this](const httplib::Request &, httplib::Response &res)
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
        
        // Parse JSON
        try {
            json root = json::parse(req.body);
            
            // Find session
            std::shared_ptr<TutoringSession> session = nullptr;
            if (sessionService) {
                session = sessionService->getSessionById(id);
            }
            
            if (!session) {
                res.status = 404;
                res.set_content("{\"error\": \"Session not found\"}", "application/json");
                setCorsHeaders(&res);
                return;
            }
            
            // Update session properties
            bool updated = false;
            
            if (root.contains("sessionDate")) {
                session->setSessionDate(root["sessionDate"]);
                updated = true;
            }
            
            if (root.contains("startTime")) {
                session->setStartTime(root["startTime"]);
                updated = true;
            }
            
            if (root.contains("durationMinutes")) {
                session->setDurationMinutes(root["durationMinutes"]);
                updated = true;
            }
            
            if (root.contains("isRemote")) {
                session->setIsRemote(root["isRemote"]);
                updated = true;
            }
            
            if (root.contains("platform")) {
                session->setPlatform(root["platform"]);
                updated = true;
            }
            
            if (root.contains("learningObjectives")) {
                session->setLearningObjectives(root["learningObjectives"]);
                updated = true;
            }
            
            bool success = false;
            if (updated && sessionService) {
                success = sessionService->updateSessionDetails(
                    id,
                    session->getSessionDate(),
                    session->getStartTime(),
                    session->getDurationMinutes()
                );
            }
            
            json response;
            response["success"] = success || updated;
            response["message"] = (success || updated) ? "Session updated successfully" : "Failed to update session";
                
            res.set_content(response.dump(), "application/json");
        } catch (const json::exception& e) {
            res.status = 400;
            res.set_content("{\"error\": \"Invalid JSON: " + std::string(e.what()) + "\"}", "application/json");
        }
        
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
    server.Get("/api/materials", [this](const httplib::Request &, httplib::Response &res)
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
        
        // Parse JSON
        try {
            json root = json::parse(req.body);
            
            // Get material
            std::shared_ptr<LearningMaterial> material = nullptr;
            if (materialService) {
                material = materialService->getMaterialById(id);
            }
            
            if (!material) {
                res.status = 404;
                res.set_content("{\"error\": \"Material not found\"}", "application/json");
                setCorsHeaders(&res);
                return;
            }
            
            // Update properties
            bool updated = false;
            
            if (root.contains("title")) {
                material->setTitle(root["title"]);
                updated = true;
            }
            
            if (root.contains("description")) {
                material->setDescription(root["description"]);
                updated = true;
            }
            
            if (root.contains("type")) {
                material->setType(root["type"]);
                updated = true;
            }
            
            if (root.contains("format")) {
                material->setFormat(root["format"]);
                updated = true;
            }
            
            if (root.contains("author")) {
                material->setAuthor(root["author"]);
                updated = true;
            }
            
            if (root.contains("difficultyLevel")) {
                material->setDifficultyLevel(root["difficultyLevel"]);
                updated = true;
            }
            
            if (root.contains("estimatedTimeMinutes")) {
                material->setEstimatedTimeMinutes(root["estimatedTimeMinutes"]);
                updated = true;
            }
            
            if (root.contains("url")) {
                material->setURL(root["url"]);
                updated = true;
            }
            
            if (root.contains("localPath")) {
                material->setLocalPath(root["localPath"]);
                updated = true;
            }
            
            bool success = false;
            if (updated && materialService) {
                success = materialService->updateMaterial(
                    id,
                    material->getTitle(),
                    material->getDescription(),
                    material->getType(),
                    material->getFormat(),
                    material->getAuthor()
                );
            }
            
            json response;
            response["success"] = success || updated;
            response["message"] = (success || updated) ? "Material updated successfully" : "Failed to update material";
                
            res.set_content(response.dump(), "application/json");
        } catch (const json::exception& e) {
            res.status = 400;
            res.set_content("{\"error\": \"Invalid JSON: " + std::string(e.what()) + "\"}", "application/json");
        }
        
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

    // Listen on the specified port
    Logger::getInstance().info("Starting server on port " + std::to_string(port));
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
    json root = json::array();

    // Get clients from the client service
    std::vector<std::shared_ptr<Client>> clients = clientService->getAllClients();

    for (const auto &client : clients)
    {
        json clientJson;
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
        json aiModelsArray = json::array();
        for (const auto &model : client->getAIModelsOfInterest())
        {
            aiModelsArray.push_back(model);
        }
        clientJson["aiModelsOfInterest"] = aiModelsArray;

        root.push_back(clientJson);
    }

    return root.dump();
}

std::string SimpleAPIServer::aiModelsToJson() const
{
    json root = json::array();

    // Get AI models from the model service
    std::vector<std::shared_ptr<AIModel>> models = aiModelService->getAllModels();

    for (const auto &model : models)
    {
        json modelJson;
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

        // Add capabilities
        json capabilitiesArray = json::array();
        for (const auto &capability : model->getCapabilities())
        {
            capabilitiesArray.push_back(capability);
        }
        modelJson["capabilities"] = capabilitiesArray;

        // Add limitations
        json limitationsArray = json::array();
        for (const auto &limitation : model->getLimitations())
        {
            limitationsArray.push_back(limitation);
        }
        modelJson["limitations"] = limitationsArray;

        // Add use cases
        json useCasesArray = json::array();
        for (const auto &useCase : model->getUseCases())
        {
            useCasesArray.push_back(useCase);
        }
        modelJson["useCases"] = useCasesArray;

        root.push_back(modelJson);
    }

    return root.dump();
}

std::string SimpleAPIServer::tutorsToJson() const
{
    json root = json::array();

    std::vector<std::shared_ptr<Tutor>> tutors;
    if (tutorService)
    {
        tutors = tutorService->getAllTutors();
    }
    else if (authService)
    {
        tutors = authService->getAllTutors();
    }

    for (const auto &tutor : tutors)
    {
        json tutorJson;
        tutorJson["userId"] = tutor->getUserId();
        tutorJson["username"] = tutor->getUsername();
        tutorJson["firstName"] = tutor->getFirstName();
        tutorJson["lastName"] = tutor->getLastName();
        tutorJson["email"] = tutor->getEmail();
        tutorJson["phone"] = tutor->getPhone();

        // Add AI specializations as array
        json specializationsArray = json::array();
        for (const auto &spec : tutor->getAISpecializations())
        {
            specializationsArray.push_back(spec);
        }
        tutorJson["aiSpecializations"] = specializationsArray;

        // Add domain expertise as array
        json expertiseArray = json::array();
        for (const auto &domain : tutor->getDomainExpertise())
        {
            expertiseArray.push_back(domain);
        }
        tutorJson["domainExpertise"] = expertiseArray;

        tutorJson["qualification"] = tutor->getQualification();
        tutorJson["experienceYears"] = tutor->getExperienceYears();
        tutorJson["hourlyRate"] = tutor->getHourlyRate();
        tutorJson["sessionsCompleted"] = tutor->getSessionsCompleted();
        tutorJson["averageRating"] = tutor->getAverageRating();

        root.push_back(tutorJson);
    }

    return root.dump();
}

std::string SimpleAPIServer::sessionsToJson() const
{
    // If we have a session service, use it. Otherwise, return mock data
    if (sessionService)
    {
        json root = json::array();

        // Get sessions from the session service
        std::vector<std::shared_ptr<TutoringSession>> sessions = sessionService->getAllSessions();

        for (const auto &session : sessions)
        {
            json sessionJson;
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
            json aiModelIdsArray = json::array();
            for (const auto &modelId : session->getAIModelIds())
            {
                aiModelIdsArray.push_back(modelId);
            }
            sessionJson["aiModelIds"] = aiModelIdsArray;

            // Add topics as array
            json topicsArray = json::array();
            for (const auto &topic : session->getTopics())
            {
                topicsArray.push_back(topic);
            }
            sessionJson["topics"] = topicsArray;

            root.push_back(sessionJson);
        }

        return root.dump();
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
        json root = json::array();

        // Get materials from the material service
        std::vector<std::shared_ptr<LearningMaterial>> materials = materialService->getAllMaterials();

        for (const auto &material : materials)
        {
            json materialJson;
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
            json aiModelIdsArray = json::array();
            for (const auto &modelId : material->getAIModelIds())
            {
                aiModelIdsArray.push_back(modelId);
            }
            materialJson["aiModelIds"] = aiModelIdsArray;

            // Add tags as array
            json tagsArray = json::array();
            for (const auto &tag : material->getTags())
            {
                tagsArray.push_back(tag);
            }
            materialJson["tags"] = tagsArray;

            root.push_back(materialJson);
        }

        return root.dump();
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

std::string SimpleAPIServer::handleSessionAdd(const std::string &requestBody)
{
    try
    {
        // Parse JSON
        json root = json::parse(requestBody);

        // Validate required fields
        if (!root.contains("clientId") || !root.contains("tutorId") ||
            !root.contains("sessionDate") || !root.contains("startTime") ||
            !root.contains("durationMinutes"))
        {
            Logger::getInstance().error("Error adding session: Missing required fields");
            return "{\"success\": false, \"error\": \"Missing required fields\"}";
        }

        // Create AI model IDs vector
        std::vector<int> aiModelIds;
        if (root.contains("aiModelIds") && root["aiModelIds"].is_array())
        {
            for (const auto &id : root["aiModelIds"])
            {
                aiModelIds.push_back(id.get<int>());
            }
        }

        // Create a session object
        auto session = std::make_shared<TutoringSession>(
            0, // ID will be assigned by the service
            root["clientId"].get<int>(),
            root["tutorId"].get<int>(),
            aiModelIds,
            root["sessionDate"].get<std::string>(),
            root["startTime"].get<std::string>(),
            root["durationMinutes"].get<int>(),
            root.contains("isRemote") ? root["isRemote"].get<bool>() : true,
            root.contains("platform") ? root["platform"].get<std::string>() : "Zoom");

        // Set additional properties
        if (root.contains("learningObjectives"))
        {
            session->setLearningObjectives(root["learningObjectives"].get<std::string>());
        }

        if (root.contains("sessionCost"))
        {
            session->setSessionCost(root["sessionCost"].get<double>());
        }
        else
        {
            // Calculate cost based on tutor hourly rate if available
            if (tutorService)
            {
                auto tutor = tutorService->getTutorById(root["tutorId"].get<int>());
                if (tutor)
                {
                    double hourlyRate = tutor->getHourlyRate();
                    double hours = root["durationMinutes"].get<double>() / 60.0;
                    session->setSessionCost(hourlyRate * hours);
                }
            }
        }

        // Add the session
        bool success = false;
        if (sessionService)
        {
            success = sessionService->scheduleSession(session);
        }

        if (success)
        {
            json response;
            response["success"] = true;
            response["sessionId"] = session->getSessionId();
            response["clientId"] = session->getClientId();
            response["tutorId"] = session->getTutorId();
            response["sessionDate"] = session->getSessionDate();
            response["startTime"] = session->getStartTime();
            response["durationMinutes"] = session->getDurationMinutes();
            response["status"] = session->getStatus();
            response["isRemote"] = session->getIsRemote();
            response["platform"] = session->getPlatform();
            response["sessionCost"] = session->getSessionCost();

            return response.dump();
        }
        else
        {
            // For demo purposes, return success even without session service
            json response;
            response["success"] = true;
            response["sessionId"] = 999;
            response["message"] = "Session scheduled successfully (mock data)";

            return response.dump();
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
        json root = json::parse(requestBody);

        // Validate required fields
        if (!root.contains("title") || !root.contains("type") ||
            !root.contains("format") || !root.contains("author"))
        {
            Logger::getInstance().error("Error adding material: Missing required fields");
            return "{\"success\": false, \"error\": \"Missing required fields\"}";
        }

        // Create a material object
        auto material = std::make_shared<LearningMaterial>(
            0, // ID will be assigned by the service
            root["title"].get<std::string>(),
            root.contains("description") ? root["description"].get<std::string>() : "",
            root["type"].get<std::string>(),
            root["format"].get<std::string>(),
            root["author"].get<std::string>());

        // Set additional properties
        if (root.contains("difficultyLevel"))
        {
            material->setDifficultyLevel(root["difficultyLevel"].get<int>());
        }

        if (root.contains("estimatedTimeMinutes"))
        {
            material->setEstimatedTimeMinutes(root["estimatedTimeMinutes"].get<int>());
        }

        if (root.contains("url"))
        {
            material->setURL(root["url"].get<std::string>());
        }

        if (root.contains("localPath"))
        {
            material->setLocalPath(root["localPath"].get<std::string>());
        }

        // Set creation date
        if (root.contains("creationDate"))
        {
            material->setCreationDate(root["creationDate"].get<std::string>());
        }
        else
        {
            // Use current date if not provided
            time_t now = time(nullptr);
            struct tm timeinfo;
            char buffer[11];
            strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtime(&now));
            material->setCreationDate(buffer);
        }

        // Add tags
        if (root.contains("tags") && root["tags"].is_array())
        {
            for (const auto &tag : root["tags"])
            {
                material->addTag(tag.get<std::string>());
            }
        }

        // Add AI model IDs
        if (root.contains("aiModelIds") && root["aiModelIds"].is_array())
        {
            for (const auto &id : root["aiModelIds"])
            {
                material->addAIModel(id.get<int>());
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
            json response;
            response["success"] = true;
            response["materialId"] = material->getMaterialId();
            response["title"] = material->getTitle();
            response["type"] = material->getType();
            response["format"] = material->getFormat();
            response["author"] = material->getAuthor();

            return response.dump();
        }
        else
        {
            // For demo purposes, return success even without material service
            json response;
            response["success"] = true;
            response["materialId"] = 999;
            response["message"] = "Material added successfully (mock data)";
            response["title"] = root["title"].get<std::string>();

            return response.dump();
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
    Logger::getInstance().info("Server stop requested");
}