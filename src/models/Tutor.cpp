#include "include/models/Tutor.h"
#include <algorithm>  // Add this line


// Default constructor
Tutor::Tutor() 
    : User(), aiSpecializations(), domainExpertise(), qualification(""), 
      experienceYears(0), aiModelExperience(), hourlyRate(0.0), 
      sessionsCompleted(0), averageRating(0.0) {}

// Parameterized constructor
Tutor::Tutor(int userId, const std::string& username, const std::string& password,
             const std::string& firstName, const std::string& lastName,
             const std::string& email, const std::string& phone,
             const std::vector<std::string>& aiSpecializations,
             const std::vector<std::string>& domainExpertise,
             const std::string& qualification, int experienceYears,
             double hourlyRate)
    : User(userId, username, password, firstName, lastName, email, phone),
      aiSpecializations(aiSpecializations), domainExpertise(domainExpertise),
      qualification(qualification), experienceYears(experienceYears),
      hourlyRate(hourlyRate), sessionsCompleted(0), averageRating(0.0) {}

// AI Specializations methods
const std::vector<std::string>& Tutor::getAISpecializations() const {
    return aiSpecializations;
}

void Tutor::addAISpecialization(const std::string& aiModel) {
    aiSpecializations.push_back(aiModel);
}

void Tutor::removeAISpecialization(const std::string& aiModel) {
    auto it = std::find(aiSpecializations.begin(), aiSpecializations.end(), aiModel);
    if (it != aiSpecializations.end()) {
        aiSpecializations.erase(it);
    }
}

bool Tutor::hasAISpecialization(const std::string& aiModel) const {
    return std::find(aiSpecializations.begin(), aiSpecializations.end(), aiModel) != aiSpecializations.end();
}

// Domain expertise methods
const std::vector<std::string>& Tutor::getDomainExpertise() const {
    return domainExpertise;
}

void Tutor::addDomainExpertise(const std::string& domain) {
    domainExpertise.push_back(domain);
}

void Tutor::removeDomainExpertise(const std::string& domain) {
    auto it = std::find(domainExpertise.begin(), domainExpertise.end(), domain);
    if (it != domainExpertise.end()) {
        domainExpertise.erase(it);
    }
}

bool Tutor::hasDomainExpertise(const std::string& domain) const {
    return std::find(domainExpertise.begin(), domainExpertise.end(), domain) != domainExpertise.end();
}

// Other getters and setters
std::string Tutor::getQualification() const { return qualification; }
void Tutor::setQualification(const std::string& qualification) { this->qualification = qualification; }

int Tutor::getExperienceYears() const { return experienceYears; }
void Tutor::setExperienceYears(int years) { this->experienceYears = years; }

int Tutor::getAIModelExperience(const std::string& aiModel) const {
    auto it = aiModelExperience.find(aiModel);
    if (it != aiModelExperience.end()) {
        return it->second;
    }
    return 0;
}

void Tutor::setAIModelExperience(const std::string& aiModel, int level) {
    aiModelExperience[aiModel] = level;
}

const std::map<std::string, int>& Tutor::getAllAIModelExperience() const {
    return aiModelExperience;
}

double Tutor::getHourlyRate() const { return hourlyRate; }
void Tutor::setHourlyRate(double rate) { this->hourlyRate = rate; }

int Tutor::getSessionsCompleted() const { return sessionsCompleted; }
void Tutor::incrementSessionsCompleted() { sessionsCompleted++; }
void Tutor::setSessionsCompleted(int count) { this->sessionsCompleted = count; }

double Tutor::getAverageRating() const { return averageRating; }

void Tutor::updateRating(double newRating) {
    if (sessionsCompleted == 0) {
        averageRating = newRating;
    } else {
        // Calculate new average
        averageRating = ((averageRating * sessionsCompleted) + newRating) / (sessionsCompleted + 1);
    }
}

// Override getRole
std::string Tutor::getRole() const {
    return "Tutor";
}

// Override displayInfo
void Tutor::displayInfo() const {
    User::displayInfo();
    std::cout << "Role: " << getRole() << std::endl;
    std::cout << "Qualification: " << qualification << std::endl;
    std::cout << "Experience (years): " << experienceYears << std::endl;
    std::cout << "Hourly Rate: $" << hourlyRate << std::endl;
    std::cout << "Sessions Completed: " << sessionsCompleted << std::endl;
    std::cout << "Average Rating: " << averageRating << std::endl;
    
    std::cout << "AI Specializations: ";
    for (const auto& spec : aiSpecializations) {
        std::cout << spec << ", ";
    }
    std::cout << std::endl;
    
    std::cout << "Domain Expertise: ";
    for (const auto& domain : domainExpertise) {
        std::cout << domain << ", ";
    }
    std::cout << std::endl;
}

// Output stream operator
std::ostream& operator<<(std::ostream& os, const Tutor& tutor) {
    os << static_cast<const User&>(tutor);
    os << "Role: " << tutor.getRole() << std::endl;
    os << "Qualification: " << tutor.qualification << std::endl;
    os << "Experience (years): " << tutor.experienceYears << std::endl;
    os << "Hourly Rate: $" << tutor.hourlyRate << std::endl;
    os << "Sessions Completed: " << tutor.sessionsCompleted << std::endl;
    os << "Average Rating: " << tutor.averageRating << std::endl;
    
    os << "AI Specializations: ";
    for (const auto& spec : tutor.aiSpecializations) {
        os << spec << ", ";
    }
    os << std::endl;
    
    os << "Domain Expertise: ";
    for (const auto& domain : tutor.domainExpertise) {
        os << domain << ", ";
    }
    os << std::endl;
    
    return os;
}

// Input stream operator
std::istream& operator>>(std::istream& is, Tutor& tutor) {
    is >> static_cast<User&>(tutor);
    
    std::cout << "Enter Qualification: ";
    std::getline(is, tutor.qualification);
    
    std::cout << "Enter Experience (years): ";
    is >> tutor.experienceYears;
    is.ignore(); // Clear newline
    
    std::cout << "Enter Hourly Rate: $";
    is >> tutor.hourlyRate;
    is.ignore(); // Clear newline
    
    std::string input;
    int count;
    
    std::cout << "How many AI Specializations? ";
    is >> count;
    is.ignore(); // Clear newline
    
    tutor.aiSpecializations.clear();
    for (int i = 0; i < count; i++) {
        std::cout << "Enter AI Specialization #" << (i+1) << ": ";
        std::getline(is, input);
        tutor.addAISpecialization(input);
    }
    
    std::cout << "How many Domain Expertise areas? ";
    is >> count;
    is.ignore(); // Clear newline
    
    tutor.domainExpertise.clear();
    for (int i = 0; i < count; i++) {
        std::cout << "Enter Domain Expertise #" << (i+1) << ": ";
        std::getline(is, input);
        tutor.addDomainExpertise(input);
    }
    
    return is;
}