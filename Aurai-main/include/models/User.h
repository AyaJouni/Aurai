// User.h
#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

// Abstract base class for all users in the system
class User {
protected:
    int userId;
    std::string username;
    std::string password;
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string phone;
    
public:
    // Constructors
    User();
    User(int userId, const std::string& username, const std::string& password,
         const std::string& firstName, const std::string& lastName,
         const std::string& email, const std::string& phone);
    
    // Virtual destructor
    virtual ~User() = default;
    
    // Getters and setters
    int getUserId() const;
    void setUserId(int userId);
    
    std::string getUsername() const;
    void setUsername(const std::string& username);
    
    std::string getPassword() const;
    void setPassword(const std::string& password);
    
    std::string getFirstName() const;
    void setFirstName(const std::string& firstName);
    
    std::string getLastName() const;
    void setLastName(const std::string& lastName);
    
    std::string getFullName() const;
    
    std::string getEmail() const;
    void setEmail(const std::string& email);
    
    std::string getPhone() const;
    void setPhone(const std::string& phone);
    
    // Pure virtual function to get role - makes this an abstract class
    virtual std::string getRole() const = 0;
    
    // Display user info
    virtual void displayInfo() const;
    
    // Operator overloading
    friend std::ostream& operator<<(std::ostream& os, const User& user);
    friend std::istream& operator>>(std::istream& is, User& user);
};

#endif // USER_H