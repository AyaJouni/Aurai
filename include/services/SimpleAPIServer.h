#ifndef SIMPLE_API_SERVER_H
#define SIMPLE_API_SERVER_H

#include <string>
#include <memory>

// Forward declarations
class AuthService;
class ClientService;
class AIModelService;
class TutorService;
class SessionService;
class LearningMaterialService;

class SimpleAPIServer
{
private:
    // References to services
    std::shared_ptr<AuthService> authService;
    std::shared_ptr<ClientService> clientService;
    std::shared_ptr<AIModelService> aiModelService;
    std::shared_ptr<TutorService> tutorService;
    std::shared_ptr<SessionService> sessionService;
    std::shared_ptr<LearningMaterialService> materialService;

    // Helper methods for JSON generation
    std::string clientsToJson() const;
    std::string aiModelsToJson() const;
    std::string tutorsToJson() const;
    std::string sessionsToJson() const;
    std::string materialsToJson() const;

    // Helper method to set CORS headers
    void setCorsHeaders(void *response);

    // Request handlers
    std::string handleClientAdd(const std::string &requestBody);
    std::string handleClientUpdate(const std::string &requestBody);
    std::string handleClientDelete(const std::string &requestBody);

    std::string handleTutorAdd(const std::string &requestBody);
    std::string handleTutorUpdate(const std::string &requestBody);
    std::string handleTutorDelete(const std::string &requestBody);

    std::string handleSessionAdd(const std::string &requestBody);
    std::string handleSessionUpdate(const std::string &requestBody);
    std::string handleSessionCancel(const std::string &requestBody);

    std::string handleMaterialAdd(const std::string &requestBody);
    std::string handleMaterialUpdate(const std::string &requestBody);
    std::string handleMaterialDelete(const std::string &requestBody);

    // Mock data methods
    std::string getMockSessions() const;
    std::string getMockMaterials() const;

public:
    // Constructor
    SimpleAPIServer(std::shared_ptr<AuthService> authService,
                    std::shared_ptr<ClientService> clientService,
                    std::shared_ptr<AIModelService> aiModelService,
                    std::shared_ptr<TutorService> tutorService = nullptr,
                    std::shared_ptr<SessionService> sessionService = nullptr,
                    std::shared_ptr<LearningMaterialService> materialService = nullptr);

    // Start the server
    void start(int port = 8080);

    // Stop the server
    void stop();

    // Check if server is running
    bool isRunning() const;
};

#endif // SIMPLE_API_SERVER_H