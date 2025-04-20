// Tutor.h
#ifndef TUTOR_H
#define TUTOR_H

#include "User.h"
#include <vector>
#include <map>

class Tutor : public User {
private:
    std::vector<std::string> aiSpecializations;    // AI systems/models they can tutor
    std::vector<std::string> domainExpertise;      // Subject matter expertise
    std::string qualification;                     // Technical qualification
    int experienceYears;                           // Years of experience with AI
    std::map<std::string, int> aiModelExperience;  // AI model and experience level (1-5)
    double hourlyRate;                             // Hourly rate for tutoring
    int sessionsCompleted;                         // Total sessions completed
    double averageRating;                          // Average rating from clients
    
public:
    // Constructors
    Tutor();
    Tutor(int userId, const std::string& username, const std::string& password,
          const std::string& firstName, const std::string& lastName,
          const std::string& email, const std::string& phone,
          const std::vector<std::string>& aiSpecializations,
          const std::vector<std::string>& domainExpertise,
          const std::string& qualification, int experienceYears,
          double hourlyRate);
    
    // Getters and setters
    const std::vector<std::string>& getAISpecializations() const;
    void addAISpecialization(const std::string& aiModel);
    void removeAISpecialization(const std::string& aiModel);
    bool hasAISpecialization(const std::string& aiModel) const;
    
    const std::vector<std::string>& getDomainExpertise() const;
    void addDomainExpertise(const std::string& domain);
    void removeDomainExpertise(const std::string& domain);
    bool hasDomainExpertise(const std::string& domain) const;
    
    std::string getQualification() const;
    void setQualification(const std::string& qualification);
    
    int getExperienceYears() const;
    void setExperienceYears(int years);
    
    int getAIModelExperience(const std::string& aiModel) const;
    void setAIModelExperience(const std::string& aiModel, int level);
    const std::map<std::string, int>& getAllAIModelExperience() const;
    
    double getHourlyRate() const;
    void setHourlyRate(double rate);
    
    int getSessionsCompleted() const;
    void incrementSessionsCompleted();
    void setSessionsCompleted(int count);
    
    double getAverageRating() const;
    void updateRating(double newRating);
    
    // Implementation of pure virtual function from User
    std::string getRole() const override;
    
    // Display tutor info (override User's displayInfo)
    void displayInfo() const override;
    
    // Operator overloading
    friend std::ostream& operator<<(std::ostream& os, const Tutor& tutor);
    friend std::istream& operator>>(std::istream& is, Tutor& tutor);
};

#endif // TUTOR_H