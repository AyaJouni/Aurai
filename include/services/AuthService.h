// AuthService.h
#ifndef AUTH_SERVICE_H
#define AUTH_SERVICE_H

#include <string>
#include <vector>
#include <memory>
#include "../models/User.h"
#include "../models/Admin.h"
#include "../models/Tutor.h"

class AuthService {
private:
    std::vector<std::shared_ptr<User>> users;
    std::shared_ptr<User> currentUser;
    bool isLoggedIn;
    
    // Private helper methods
    void loadUsers();  // Load users from file
    void saveUsers();  // Save users to file
    
public:
    // Constructor and Destructor
    AuthService();
    ~AuthService();
    
    // User authentication methods
    bool login(const std::string& username, const std::string& password);
    void logout();
    bool isUserLoggedIn() const;
    std::shared_ptr<User> getCurrentUser() const;
    
    // User management methods
    bool registerUser(std::shared_ptr<User> user);
    bool deleteUser(int userId);
    bool updateUserPassword(int userId, const std::string& newPassword);
    bool updateUserDetails(int userId, const std::string& firstName, 
                         const std::string& lastName, const std::string& email,
                         const std::string& phone);
    
    // User retrieval methods
    std::shared_ptr<User> getUserById(int userId) const;
    std::shared_ptr<User> getUserByUsername(const std::string& username) const;
    std::vector<std::shared_ptr<User>> getAllUsers() const;
    std::vector<std::shared_ptr<Tutor>> getAllTutors() const;
    std::vector<std::shared_ptr<Admin>> getAllAdmins() const;
    
    // Authorization methods
    bool isAdmin() const;
    bool isTutor() const;
    bool hasPermission(const std::string& permission) const;
};

#endif // AUTH_SERVICE_H