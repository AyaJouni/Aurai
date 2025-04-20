// SessionService.h
#ifndef SESSION_SERVICE_H
#define SESSION_SERVICE_H

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "../models/TutoringSession.h"

class SessionService {
private:
    std::vector<std::shared_ptr<TutoringSession>> sessions;
    int nextSessionId;
    
    // Private helper methods
    void loadSessions();  // Load sessions from file
    void saveSessions();  // Save sessions to file
    bool isValidDate(const std::string& date) const;
    bool isValidTime(const std::string& time) const;
    bool isTutorAvailable(int tutorId, const std::string& date, 
                        const std::string& startTime, int durationMinutes) const;
    
public:
    // Constructor and Destructor
    SessionService();
    ~SessionService();
    
    // Session management methods
    bool scheduleSession(std::shared_ptr<TutoringSession> session);
    bool cancelSession(int sessionId, const std::string& reason);
    bool completeSession(int sessionId, double clientRating, 
                       const std::string& notes, const std::string& skillsGained);
    bool updateSessionDetails(int sessionId, const std::string& date, 
                            const std::string& startTime, int durationMinutes);
    
    // Session retrieval methods
    std::shared_ptr<TutoringSession> getSessionById(int sessionId) const;
    std::vector<std::shared_ptr<TutoringSession>> getAllSessions() const;
    std::vector<std::shared_ptr<TutoringSession>> getClientSessions(int clientId) const;
    std::vector<std::shared_ptr<TutoringSession>> getTutorSessions(int tutorId) const;
    std::vector<std::shared_ptr<TutoringSession>> getSessionsByDate(const std::string& date) const;
    std::vector<std::shared_ptr<TutoringSession>> getSessionsByAIModel(int aiModelId) const;
    std::vector<std::shared_ptr<TutoringSession>> getUpcomingSessions() const;
    std::vector<std::shared_ptr<TutoringSession>> getCompletedSessions() const;
    
    // Session content management
    bool addSessionTopic(int sessionId, const std::string& topic);
    bool setSessionObjectives(int sessionId, const std::string& objectives);
    bool assignSessionHomework(int sessionId, const std::string& homework);
    
    // Payment management
    bool updateSessionPayment(int sessionId, double cost, const std::string& status);
    bool markSessionAsPaid(int sessionId);
    std::vector<std::shared_ptr<TutoringSession>> getUnpaidSessions() const;
    
    // Analytics methods
    double getAverageSessionRating() const;
    std::map<std::string, int> getPopularSessionTopics() const;
    std::map<int, int> getSessionsByAIModelCount() const;
    double getTotalRevenue(const std::string& startDate, const std::string& endDate) const;
    double getAverageSessionDuration() const;
};

#endif // SESSION_SERVICE_H