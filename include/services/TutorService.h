// TutorService.h
#ifndef TUTOR_SERVICE_H
#define TUTOR_SERVICE_H

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "../models/Tutor.h"

class TutorService {
private:
    std::vector<std::shared_ptr<Tutor>> tutors;
    
    // Private helper methods
    void loadTutors();  // Load tutors from file (if not using AuthService)
    void saveTutors();  // Save tutors to file (if not using AuthService)
    
public:
    // Constructor and Destructor
    TutorService();
    ~TutorService();
    
    // Tutor retrieval methods (if not using AuthService)
    std::shared_ptr<Tutor> getTutorById(int tutorId) const;
    std::vector<std::shared_ptr<Tutor>> getAllTutors() const;
    
    // Expertise management
    bool addTutorSpecialization(int tutorId, const std::string& aiModel);
    bool removeTutorSpecialization(int tutorId, const std::string& aiModel);
    bool addTutorDomainExpertise(int tutorId, const std::string& domain);
    bool removeTutorDomainExpertise(int tutorId, const std::string& domain);
    
    // AI Model experience
    bool updateTutorModelExperience(int tutorId, const std::string& aiModel, int experienceLevel);
    std::map<std::string, int> getTutorModelExperience(int tutorId) const;
    
    // Tutor search methods
    std::vector<std::shared_ptr<Tutor>> getTutorsBySpecialization(const std::string& aiModel) const;
    std::vector<std::shared_ptr<Tutor>> getTutorsByDomain(const std::string& domain) const;
    std::vector<std::shared_ptr<Tutor>> getTutorsByExperience(int minYearsExperience) const;
    
    // Tutor rating management
    bool updateTutorRating(int tutorId, double newRating);
    double getTutorAverageRating(int tutorId) const;
    
    // Tutor session management
    bool incrementTutorSessions(int tutorId);
    int getTutorCompletedSessions(int tutorId) const;
    
    // Rate management
    bool updateTutorRate(int tutorId, double hourlyRate);
    double getTutorRate(int tutorId) const;
    
    // Analytics methods
    std::map<std::string, int> getPopularSpecializations() const;
    std::vector<std::shared_ptr<Tutor>> getTopRatedTutors(int count) const;
    std::vector<std::shared_ptr<Tutor>> getMostExperiencedTutors(int count) const;
    
    // Matching algorithms
    std::vector<std::shared_ptr<Tutor>> findMatchingTutorsForClient(int clientId, 
                                                                  const std::vector<std::string>& aiModels) const;
    std::shared_ptr<Tutor> getBestTutorMatch(int clientId, const std::string& aiModel) const;
};

#endif // TUTOR_SERVICE_H