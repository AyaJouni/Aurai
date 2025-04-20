#include "include/models/Client.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

// Default constructor
Client::Client() 
    : clientId(0), firstName(""), lastName(""), email(""), phone(""),
      company(""), position(""), aiModelsOfInterest(), learningGoals(),
      aiModelProficiency(), registrationDate(""), sessionsCompleted(0),
      lastSessionDate(""), budget(0.0) {}

// Parameterized constructor
Client::Client(int clientId, const std::string& firstName, const std::string& lastName,
               const std::string& email, const std::string& phone, const std::string& company,
               const std::string& position)
    : clientId(clientId), firstName(firstName), lastName(lastName), email(email),
      phone(phone), company(company), position(position), aiModelsOfInterest(),
      learningGoals(), aiModelProficiency(), registrationDate(""), 
      sessionsCompleted(0), lastSessionDate(""), budget(0.0) {}

// Getters and setters
int Client::getClientId() const { return clientId; }
void Client::setClientId(int id) { clientId = id; }

std::string Client::getFirstName() const { return firstName; }
void Client::setFirstName(const std::string& firstName) { this->firstName = firstName; }

std::string Client::getLastName() const { return lastName; }
void Client::setLastName(const std::string& lastName) { this->lastName = lastName; }

std::string Client::getFullName() const { return firstName + " " + lastName; }

std::string Client::getEmail() const { return email; }
void Client::setEmail(const std::string& email) { this->email = email; }

std::string Client::getPhone() const { return phone; }
void Client::setPhone(const std::string& phone) { this->phone = phone; }

std::string Client::getCompany() const { return company; }
void Client::setCompany(const std::string& company) { this->company = company; }

std::string Client::getPosition() const { return position; }
void Client::setPosition(const std::string& position) { this->position = position; }

// AI models of interest methods
const std::vector<std::string>& Client::getAIModelsOfInterest() const {
    return aiModelsOfInterest;
}

void Client::addAIModel(const std::string& model) {
    // Check if the model is already in the list
    if (!isInterestedIn(model)) {
        aiModelsOfInterest.push_back(model);
    }
}

void Client::removeAIModel(const std::string& model) {
    auto it = std::find(aiModelsOfInterest.begin(), aiModelsOfInterest.end(), model);
    if (it != aiModelsOfInterest.end()) {
        aiModelsOfInterest.erase(it);
    }
}

bool Client::isInterestedIn(const std::string& model) const {
    return std::find(aiModelsOfInterest.begin(), aiModelsOfInterest.end(), model) != aiModelsOfInterest.end();
}

// Learning goals methods
const std::vector<std::string>& Client::getLearningGoals() const {
    return learningGoals;
}

void Client::addLearningGoal(const std::string& goal) {
    learningGoals.push_back(goal);
}

void Client::removeLearningGoal(const std::string& goal) {
    auto it = std::find(learningGoals.begin(), learningGoals.end(), goal);
    if (it != learningGoals.end()) {
        learningGoals.erase(it);
    }
}

// AI model proficiency methods
int Client::getAIModelProficiency(const std::string& model) const {
    auto it = aiModelProficiency.find(model);
    if (it != aiModelProficiency.end()) {
        return it->second;
    }
    return 0; // No proficiency by default
}

void Client::setAIModelProficiency(const std::string& model, int level) {
    // Ensure level is between 1 and 5
    if (level >= 1 && level <= 5) {
        aiModelProficiency[model] = level;
    }
}

const std::map<std::string, int>& Client::getAllProficiencies() const {
    return aiModelProficiency;
}

// Session tracking methods
std::string Client::getRegistrationDate() const { return registrationDate; }
void Client::setRegistrationDate(const std::string& date) { registrationDate = date; }

int Client::getSessionsCompleted() const { return sessionsCompleted; }
void Client::incrementSessionsCompleted() { sessionsCompleted++; }
void Client::setSessionsCompleted(int count) { sessionsCompleted = count; }

std::string Client::getLastSessionDate() const { return lastSessionDate; }
void Client::setLastSessionDate(const std::string& date) { lastSessionDate = date; }

// Budget methods
double Client::getBudget() const { return budget; }
void Client::setBudget(double amount) { budget = amount; }

void Client::deductFromBudget(double amount) {
    if (amount <= budget) {
        budget -= amount;
    } else {
        budget = 0.0;
    }
}

void Client::addToBudget(double amount) {
    budget += amount;
}

// Display methods
void Client::displayInfo() const {
    std::cout << "Client ID: " << clientId << std::endl;
    std::cout << "Name: " << getFullName() << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Phone: " << phone << std::endl;
    std::cout << "Company: " << company << std::endl;
    std::cout << "Position: " << position << std::endl;
    std::cout << "Registration Date: " << registrationDate << std::endl;
    std::cout << "Sessions Completed: " << sessionsCompleted << std::endl;
    std::cout << "Last Session: " << lastSessionDate << std::endl;
    std::cout << "Budget: $" << std::fixed << std::setprecision(2) << budget << std::endl;
    
    std::cout << "\nAI Models of Interest: ";
    for (const auto& model : aiModelsOfInterest) {
        std::cout << model << ", ";
    }
    std::cout << std::endl;
    
    std::cout << "Learning Goals: ";
    for (const auto& goal : learningGoals) {
        std::cout << goal << ", ";
    }
    std::cout << std::endl;
}

void Client::displayProficiencies() const {
    std::cout << "Proficiency Levels for " << getFullName() << ":" << std::endl;
    
    for (const auto& proficiency : aiModelProficiency) {
        std::cout << proficiency.first << ": ";
        
        // Display stars for proficiency level
        for (int i = 0; i < proficiency.second; i++) {
            std::cout << "★";
        }
        for (int i = proficiency.second; i < 5; i++) {
            std::cout << "☆";
        }
        
        std::cout << " (" << proficiency.second << "/5)" << std::endl;
    }
}

// Operator overloading
std::ostream& operator<<(std::ostream& os, const Client& client) {
    os << "Client ID: " << client.clientId << std::endl;
    os << "Name: " << client.getFullName() << std::endl;
    os << "Email: " << client.email << std::endl;
    os << "Phone: " << client.phone << std::endl;
    os << "Company: " << client.company << std::endl;
    os << "Position: " << client.position << std::endl;
    os << "Registration Date: " << client.registrationDate << std::endl;
    os << "Sessions Completed: " << client.sessionsCompleted << std::endl;
    os << "Last Session: " << client.lastSessionDate << std::endl;
    os << "Budget: $" << std::fixed << std::setprecision(2) << client.budget << std::endl;
    
    os << "AI Models of Interest: ";
    for (size_t i = 0; i < client.aiModelsOfInterest.size(); i++) {
        os << client.aiModelsOfInterest[i];
        if (i < client.aiModelsOfInterest.size() - 1) {
            os << ", ";
        }
    }
    os << std::endl;
    
    return os;
}

std::istream& operator>>(std::istream& is, Client& client) {
    std::cout << "Enter Client ID: ";
    is >> client.clientId;
    is.ignore(); // Clear newline
    
    std::cout << "Enter First Name: ";
    std::getline(is, client.firstName);
    
    std::cout << "Enter Last Name: ";
    std::getline(is, client.lastName);
    
    std::cout << "Enter Email: ";
    std::getline(is, client.email);
    
    std::cout << "Enter Phone: ";
    std::getline(is, client.phone);
    
    std::cout << "Enter Company: ";
    std::getline(is, client.company);
    
    std::cout << "Enter Position: ";
    std::getline(is, client.position);
    
    std::cout << "Enter Registration Date (YYYY-MM-DD): ";
    std::getline(is, client.registrationDate);
    
    std::cout << "Enter Number of Sessions Completed: ";
    is >> client.sessionsCompleted;
    is.ignore(); // Clear newline
    
    std::cout << "Enter Budget: $";
    is >> client.budget;
    is.ignore(); // Clear newline
    
    // AI models of interest would typically be added in a separate operation
    // for better user experience
    
    return is;
}