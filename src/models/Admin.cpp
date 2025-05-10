#include "include/models/Admin.h"

// Default constructor
Admin::Admin() : User(), accessLevel(""), canManageAI(false), canManageUsers(false), lastLogin("") {}

// Parameterized constructor
Admin::Admin(int userId, const std::string& username, const std::string& password,
             const std::string& firstName, const std::string& lastName,
             const std::string& email, const std::string& phone,
             const std::string& accessLevel, bool canManageAI, bool canManageUsers)
    : User(userId, username, password, firstName, lastName, email, phone),
      accessLevel(accessLevel), canManageAI(canManageAI), canManageUsers(canManageUsers), lastLogin("") {}

// Getters
std::string Admin::getAccessLevel() const { return accessLevel; }
bool Admin::getCanManageAI() const { return canManageAI; }
bool Admin::getCanManageUsers() const { return canManageUsers; }
std::string Admin::getLastLogin() const { return lastLogin; }

// Setters
void Admin::setAccessLevel(const std::string& accessLevel) { this->accessLevel = accessLevel; }
void Admin::setCanManageAI(bool permission) { this->canManageAI = permission; }
void Admin::setCanManageUsers(bool permission) { this->canManageUsers = permission; }
void Admin::setLastLogin(const std::string& timestamp) { this->lastLogin = timestamp; }

// Override getRole
std::string Admin::getRole() const {
    return "Admin";
}

// Override displayInfo
void Admin::displayInfo() const {
    User::displayInfo();
    std::cout << "Role: " << getRole() << std::endl;
    std::cout << "Access Level: " << accessLevel << std::endl;
    std::cout << "Can Manage AI: " << (canManageAI ? "Yes" : "No") << std::endl;
    std::cout << "Can Manage Users: " << (canManageUsers ? "Yes" : "No") << std::endl;
    std::cout << "Last Login: " << lastLogin << std::endl;
}

// Admin-specific functions (stub implementations)
bool Admin::createUser(User& newUser) const {
    std::cout << "Admin creating new user: " << newUser.getUsername() << std::endl;
    return true;
}

bool Admin::deleteUser(int userId) const {
    std::cout << "Admin deleting user with ID: " << userId << std::endl;
    return true;
}

bool Admin::resetUserPassword(int userId, const std::string& newPassword) const {
    std::cout << "Admin resetting password for user ID: " << userId << std::endl;
    return true;
}

bool Admin::updateAISettings(int aiId, const std::string& setting, const std::string& value) const {
    std::cout << "Admin updating AI settings for AI ID: " << aiId << std::endl;
    std::cout << "Setting: " << setting << " to value: " << value << std::endl;
    return true;
}

// Output stream operator
std::ostream& operator<<(std::ostream& os, const Admin& admin) {
    os << static_cast<const User&>(admin);
    os << "Role: " << admin.getRole() << std::endl;
    os << "Access Level: " << admin.accessLevel << std::endl;
    os << "Can Manage AI: " << (admin.canManageAI ? "Yes" : "No") << std::endl;
    os << "Can Manage Users: " << (admin.canManageUsers ? "Yes" : "No") << std::endl;
    os << "Last Login: " << admin.lastLogin << std::endl;
    return os;
}

// Input stream operator
std::istream& operator>>(std::istream& is, Admin& admin) {
    is >> static_cast<User&>(admin);
    
    std::cout << "Enter Access Level: ";
    std::getline(is, admin.accessLevel);
    
    std::string input;
    std::cout << "Can Manage AI (y/n): ";
    std::getline(is, input);
    admin.canManageAI = (input == "y" || input == "Y");
    
    std::cout << "Can Manage Users (y/n): ";
    std::getline(is, input);
    admin.canManageUsers = (input == "y" || input == "Y");

    return is;
}