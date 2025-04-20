#include "include/services/AuthService.h"
#include "include/utils/Logger.h"
#include "include/utils/Exception.h"
#include <iostream>
#include <fstream>
#include <algorithm>  // Add this line


// Constructor
AuthService::AuthService() : currentUser(nullptr), isLoggedIn(false) {
    loadUsers();
}

// Destructor
AuthService::~AuthService() {
    saveUsers();
}

// Load users from file (stub implementation)
void AuthService::loadUsers() {
    // In a real implementation, this would load from a file
    // For now, we'll create some hardcoded users for testing
    
    // Create an admin user
    auto admin = std::make_shared<Admin>(
        1, "admin", "admin123", 
        "Admin", "User", 
        "admin@example.com", "555-1234", 
        "Full", true, true
    );
    users.push_back(admin);
    
    // Create a tutor
    std::vector<std::string> aiSpecializations = {"Large Language Models", "Computer Vision"};
    std::vector<std::string> domainExpertise = {"Natural Language Processing", "Neural Networks"};
    
    auto tutor = std::make_shared<Tutor>(
        2, "tutor", "tutor123", 
        "Tutor", "User", 
        "tutor@example.com", "555-5678",
        aiSpecializations, domainExpertise,
        "PhD in Computer Science", 5, 75.0
    );
    users.push_back(tutor);
    
    Logger::getInstance().info("Loaded " + std::to_string(users.size()) + " users");
}

// Save users to file (stub implementation)
void AuthService::saveUsers() {
    // In a real implementation, this would save to a file
    Logger::getInstance().info("Saved " + std::to_string(users.size()) + " users");
}

// User authentication
bool AuthService::login(const std::string& username, const std::string& password) {
    for (const auto& user : users) {
        if (user->getUsername() == username && user->getPassword() == password) {
            currentUser = user;
            isLoggedIn = true;
            return true;
        }
    }
    return false;
}

void AuthService::logout() {
    currentUser = nullptr;
    isLoggedIn = false;
}

bool AuthService::isUserLoggedIn() const {
    return isLoggedIn;
}

std::shared_ptr<User> AuthService::getCurrentUser() const {
    return currentUser;
}

// User management methods (stub implementations)
bool AuthService::registerUser(std::shared_ptr<User> user) {
    users.push_back(user);
    saveUsers();
    return true;
}

bool AuthService::deleteUser(int userId) {
    auto it = std::find_if(users.begin(), users.end(), 
        [userId](const std::shared_ptr<User>& user) {
            return user->getUserId() == userId;
        });
    
    if (it != users.end()) {
        users.erase(it);
        saveUsers();
        return true;
    }
    return false;
}

bool AuthService::updateUserPassword(int userId, const std::string& newPassword) {
    auto user = getUserById(userId);
    if (user) {
        user->setPassword(newPassword);
        saveUsers();
        return true;
    }
    return false;
}

bool AuthService::updateUserDetails(int userId, const std::string& firstName, 
                                   const std::string& lastName, const std::string& email,
                                   const std::string& phone) {
    auto user = getUserById(userId);
    if (user) {
        user->setFirstName(firstName);
        user->setLastName(lastName);
        user->setEmail(email);
        user->setPhone(phone);
        saveUsers();
        return true;
    }
    return false;
}

// User retrieval methods
std::shared_ptr<User> AuthService::getUserById(int userId) const {
    for (const auto& user : users) {
        if (user->getUserId() == userId) {
            return user;
        }
    }
    return nullptr;
}

std::shared_ptr<User> AuthService::getUserByUsername(const std::string& username) const {
    for (const auto& user : users) {
        if (user->getUsername() == username) {
            return user;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<User>> AuthService::getAllUsers() const {
    return users;
}

std::vector<std::shared_ptr<Tutor>> AuthService::getAllTutors() const {
    std::vector<std::shared_ptr<Tutor>> tutors;
    
    for (const auto& user : users) {
        if (user->getRole() == "Tutor") {
            tutors.push_back(std::dynamic_pointer_cast<Tutor>(user));
        }
    }
    
    return tutors;
}

std::vector<std::shared_ptr<Admin>> AuthService::getAllAdmins() const {
    std::vector<std::shared_ptr<Admin>> admins;
    
    for (const auto& user : users) {
        if (user->getRole() == "Admin") {
            admins.push_back(std::dynamic_pointer_cast<Admin>(user));
        }
    }
    
    return admins;
}

// Authorization methods
bool AuthService::isAdmin() const {
    if (!isUserLoggedIn() || !currentUser) {
        return false;
    }
    return currentUser->getRole() == "Admin";
}

bool AuthService::isTutor() const {
    if (!isUserLoggedIn() || !currentUser) {
        return false;
    }
    return currentUser->getRole() == "Tutor";
}

bool AuthService::hasPermission(const std::string& permission) const {
    if (!isUserLoggedIn() || !currentUser) {
        return false;
    }
    
    // Simple permission check stub
    if (isAdmin()) {
        return true; // Admins have all permissions
    }
    
    // For tutors, could implement specific permission checks
    return false;
}