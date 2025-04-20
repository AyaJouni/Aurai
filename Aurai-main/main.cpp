#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <thread>

// Include all necessary header files
#include "include/models/User.h"
#include "include/models/Admin.h"
#include "include/models/Tutor.h"
#include "include/models/Client.h"
#include "include/models/AIModel.h"
#include "include/models/TutoringSession.h"
#include "include/models/LearningMaterial.h"

#include "include/services/AuthService.h"
#include "include/services/ClientService.h"
#include "include/services/TutorService.h"
#include "include/services/SessionService.h"
#include "include/services/AIModelService.h"
#include "include/services/LearningMaterialService.h"
#include "include/services/ReportService.h"
#include "include/services/FileService.h"
#include "include/services/SimpleAPIServer.h"

#include "include/utils/Exception.h"
#include "include/utils/Validation.h"
#include "include/utils/Menu.h"
#include "include/utils/Logger.h"

// Global service instances
std::shared_ptr<AuthService> authService;
std::shared_ptr<ClientService> clientService;
std::shared_ptr<TutorService> tutorService;
std::shared_ptr<SessionService> sessionService;
std::shared_ptr<AIModelService> aiModelService;
std::shared_ptr<LearningMaterialService> materialService;
std::shared_ptr<ReportService> reportService;
std::shared_ptr<SimpleAPIServer> apiServer;
MenuManager menuManager;

// Function prototypes
void initializeServices();
void startAPIServer();
void createMainMenu();
void handleLogin();
void handleLogout();

int main()
{
    std::cout << "==================================================" << std::endl;
    std::cout << "     AI Tutoring Center CRM System" << std::endl;
    std::cout << "     Lebanese American University" << std::endl;
    std::cout << "==================================================" << std::endl;

    try
    {
        // Initialize services
        initializeServices();

        // Start API server in a separate thread
        std::thread apiThread(startAPIServer);
        apiThread.detach(); // Let it run independently

        // Create main menu structure
        createMainMenu();

        // Start with login menu
        menuManager.getMenu(0).run(); // Main menu
    }
    catch (const CRMException &e)
    {
        std::cerr << "Application Error: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Unexpected Error: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Thank you for using the AI Tutoring Center CRM System!" << std::endl;
    return 0;
}

void initializeServices()
{
    // Create service instances for implemented services
    authService = std::make_shared<AuthService>();
    clientService = std::make_shared<ClientService>();
    aiModelService = std::make_shared<AIModelService>();

    // Initialize unimplemented services as null
    tutorService = nullptr;
    sessionService = nullptr;
    materialService = nullptr;
    reportService = nullptr;

    // Initialize the SimpleAPIServer with the services
    apiServer = std::make_shared<SimpleAPIServer>(
        authService,
        clientService,
        aiModelService,
        tutorService,
        sessionService,
        materialService);

    // Log system startup
    Logger::getInstance().info("CRM System started");
}

void startAPIServer()
{
    try
    {
        Logger::getInstance().info("Starting API server thread");

        // Print when starting the server
        Logger::getInstance().info("Before creating server");
        httplib::Server svr;

        // Print when adding routes
        Logger::getInstance().info("Adding routes");
        svr.Get("/", [](const httplib::Request &, httplib::Response &res)
                { res.set_content("Hello World!", "text/plain"); });

        // Print when starting to listen
        Logger::getInstance().info("Starting to listen on port 8080");
        svr.listen("0.0.0.0", 8080);

        // This line will only execute if listen() returns, which normally doesn't happen
        Logger::getInstance().info("Server stopped listening");
    }
    catch (const std::exception &e)
    {
        Logger::getInstance().error("API server error: " + std::string(e.what()));
    }
    catch (...)
    {
        Logger::getInstance().error("Unknown API server error");
    }
}

void createMainMenu()
{
    // Create all menus
    int mainMenuIndex = menuManager.addMenu("AI Tutoring Center CRM System", false);
    int loginMenuIndex = menuManager.addMenu("Login", true);
    int adminMenuIndex = menuManager.addMenu("Administrator Menu", false);
    int tutorMenuIndex = menuManager.addMenu("Tutor Menu", false);

    // Main menu
    menuManager.getMenu(mainMenuIndex).addItem("Login", [loginMenuIndex]()
                                               { menuManager.getMenu(loginMenuIndex).run(); });

    menuManager.getMenu(mainMenuIndex).addItem("Exit", []()
                                               {
        std::cout << "Exiting system..." << std::endl;
        exit(0); });

    // Login menu
    menuManager.getMenu(loginMenuIndex).addItem("Enter Credentials", []()
                                                { handleLogin(); });

    // Admin menu
    menuManager.getMenu(adminMenuIndex).addItem("Logout", []()
                                                { handleLogout(); });

    // Tutor menu
    menuManager.getMenu(tutorMenuIndex).addItem("Logout", []()
                                                { handleLogout(); });
}

void handleLogin()
{
    std::string username, password;

    std::cout << "Username: ";
    std::getline(std::cin, username);

    std::cout << "Password: ";
    std::getline(std::cin, password);

    try
    {
        bool success = authService->login(username, password);

        if (success)
        {
            Logger::getInstance().info("User logged in: " + username);

            if (authService->isAdmin())
            {
                std::cout << "Admin login successful!" << std::endl;
                menuManager.getMenu(2).run(); // Admin menu
            }
            else if (authService->isTutor())
            {
                std::cout << "Tutor login successful!" << std::endl;
                menuManager.getMenu(3).run(); // Tutor menu
            }
        }
        else
        {
            std::cout << "Login failed. Invalid username or password." << std::endl;
            Logger::getInstance().warning("Failed login attempt: " + username);
        }
    }
    catch (const CRMException &e)
    {
        std::cout << "Login error: " << e.what() << std::endl;
        Logger::getInstance().error("Login error: " + std::string(e.what()));
    }
}

void handleLogout()
{
    if (authService->isUserLoggedIn())
    {
        std::string username = authService->getCurrentUser()->getUsername();
        authService->logout();
        std::cout << "Logged out successfully." << std::endl;
        Logger::getInstance().info("User logged out: " + username);
    }
}