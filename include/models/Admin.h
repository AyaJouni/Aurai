// Admin.h
#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"

class Admin : public User {
private:
    std::string accessLevel;    // "Full", "Limited", etc.
    bool canManageAI;           // Permission to modify AI settings
    bool canManageUsers;        // Permission to add/delete users
    std::string lastLogin;      // Last login timestamp
    
public:
    // Constructors
    Admin();
    Admin(int userId, const std::string& username, const std::string& password,
          const std::string& firstName, const std::string& lastName,
          const std::string& email, const std::string& phone,
          const std::string& accessLevel, bool canManageAI, bool canManageUsers);
    
    // Getters and setters
    std::string getAccessLevel() const;
    void setAccessLevel(const std::string& accessLevel);
    
    bool getCanManageAI() const;
    void setCanManageAI(bool permission);
    
    bool getCanManageUsers() const;
    void setCanManageUsers(bool permission);
    
    std::string getLastLogin() const;
    void setLastLogin(const std::string& timestamp);
    
    // Implementation of pure virtual function from User
    std::string getRole() const override;
    
    // Display admin info (override User's displayInfo)
    void displayInfo() const override;
    
    // Admin-specific functions
    bool createUser(User& newUser) const;
    bool deleteUser(int userId) const;
    bool resetUserPassword(int userId, const std::string& newPassword) const;
    bool updateAISettings(int aiId, const std::string& setting, const std::string& value) const;
    
    // Operator overloading
    friend std::ostream& operator<<(std::ostream& os, const Admin& admin);
    friend std::istream& operator>>(std::istream& is, Admin& admin);
};

#endif // ADMIN_H