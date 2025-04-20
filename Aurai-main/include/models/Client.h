// Client.h
#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include <map>
#include <iostream>

class Client {
private:
    int clientId;
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string phone;
    std::string company;
    std::string position;
    std::vector<std::string> aiModelsOfInterest;    // AI models they want to learn
    std::vector<std::string> learningGoals;         // What they want to accomplish
    std::map<std::string, int> aiModelProficiency;  // Current proficiency level (1-5)
    std::string registrationDate;
    int sessionsCompleted;
    std::string lastSessionDate;
    double budget;                                  // Available budget for tutoring
    
public:
    // Constructors
    Client();
    Client(int clientId, const std::string& firstName, const std::string& lastName,
           const std::string& email, const std::string& phone, const std::string& company,
           const std::string& position);
    
    // Getters and setters
    int getClientId() const;
    void setClientId(int id);
    
    std::string getFirstName() const;
    void setFirstName(const std::string& firstName);
    
    std::string getLastName() const;
    void setLastName(const std::string& lastName);
    
    std::string getFullName() const;
    
    std::string getEmail() const;
    void setEmail(const std::string& email);
    
    std::string getPhone() const;
    void setPhone(const std::string& phone);
    
    std::string getCompany() const;
    void setCompany(const std::string& company);
    
    std::string getPosition() const;
    void setPosition(const std::string& position);
    
    // AI models of interest
    const std::vector<std::string>& getAIModelsOfInterest() const;
    void addAIModel(const std::string& model);
    void removeAIModel(const std::string& model);
    bool isInterestedIn(const std::string& model) const;
    
    // Learning goals
    const std::vector<std::string>& getLearningGoals() const;
    void addLearningGoal(const std::string& goal);
    void removeLearningGoal(const std::string& goal);
    
    // AI model proficiency
    int getAIModelProficiency(const std::string& model) const;
    void setAIModelProficiency(const std::string& model, int level);
    const std::map<std::string, int>& getAllProficiencies() const;
    
    // Session tracking
    std::string getRegistrationDate() const;
    void setRegistrationDate(const std::string& date);
    
    int getSessionsCompleted() const;
    void incrementSessionsCompleted();
    void setSessionsCompleted(int count);
    
    std::string getLastSessionDate() const;
    void setLastSessionDate(const std::string& date);
    
    double getBudget() const;
    void setBudget(double amount);
    void deductFromBudget(double amount);
    void addToBudget(double amount);
    
    // Display client info
    void displayInfo() const;
    void displayProficiencies() const;
    
    // Operator overloading
    friend std::ostream& operator<<(std::ostream& os, const Client& client);
    friend std::istream& operator>>(std::istream& is, Client& client);
};

#endif // CLIENT_H