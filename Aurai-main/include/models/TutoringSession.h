// TutoringSession.h
#ifndef TUTORING_SESSION_H
#define TUTORING_SESSION_H

#include <string>
#include <vector>
#include <iostream>

class TutoringSession {
private:
    int sessionId;
    int clientId;
    int tutorId;
    std::vector<int> aiModelIds;       // IDs of AI models covered in session
    std::string sessionDate;           // Date of the session (YYYY-MM-DD)
    std::string startTime;             // Start time (HH:MM)
    int durationMinutes;               // Duration in minutes
    std::string status;                // "Scheduled", "Completed", "Cancelled"
    double clientRating;               // Rating given by client (1-5)
    std::string learningObjectives;    // Objectives for the session
    std::string sessionNotes;          // Notes about what was covered
    std::vector<std::string> topics;   // Specific topics covered
    std::string skillsGained;          // Skills the client gained
    std::string homeworkAssigned;      // Any practice assigned after session
    double sessionCost;                // Cost of the session
    std::string paymentStatus;         // "Paid", "Pending", "Refunded"
    bool isRemote;                     // Remote or in-person session
    std::string platform;              // If remote, what platform was used
    
public:
    // Constructors
    TutoringSession();
    TutoringSession(int sessionId, int clientId, int tutorId, 
                    const std::vector<int>& aiModelIds,
                    const std::string& sessionDate, const std::string& startTime,
                    int durationMinutes, bool isRemote = true,
                    const std::string& platform = "Zoom");
    
    // Getters and setters
    int getSessionId() const;
    void setSessionId(int id);
    
    int getClientId() const;
    void setClientId(int id);
    
    int getTutorId() const;
    void setTutorId(int id);
    
    const std::vector<int>& getAIModelIds() const;
    void addAIModel(int modelId);
    void removeAIModel(int modelId);
    bool includesAIModel(int modelId) const;
    
    std::string getSessionDate() const;
    void setSessionDate(const std::string& date);
    
    std::string getStartTime() const;
    void setStartTime(const std::string& time);
    
    int getDurationMinutes() const;
    void setDurationMinutes(int duration);
    
    std::string getStatus() const;
    void setStatus(const std::string& status);
    
    double getClientRating() const;
    void setClientRating(double rating);
    
    std::string getLearningObjectives() const;
    void setLearningObjectives(const std::string& objectives);
    
    std::string getSessionNotes() const;
    void setSessionNotes(const std::string& notes);
    
    const std::vector<std::string>& getTopics() const;
    void addTopic(const std::string& topic);
    void removeTopic(const std::string& topic);
    
    std::string getSkillsGained() const;
    void setSkillsGained(const std::string& skills);
    
    std::string getHomeworkAssigned() const;
    void setHomeworkAssigned(const std::string& homework);
    
    double getSessionCost() const;
    void setSessionCost(double cost);
    
    std::string getPaymentStatus() const;
    void setPaymentStatus(const std::string& status);
    
    bool getIsRemote() const;
    void setIsRemote(bool remote);
    
    std::string getPlatform() const;
    void setPlatform(const std::string& platform);
    
    // Utility methods
    void completeSession(double rating, const std::string& notes, 
                         const std::string& skillsGained);
    void cancelSession(const std::string& reason);
    std::string getFormattedDuration() const; // Returns "HH:MM" format
    
    // Display session info
    void displayInfo() const;
    void displayTopics() const;
    
    // Operator overloading
    friend std::ostream& operator<<(std::ostream& os, const TutoringSession& session);
    friend std::istream& operator>>(std::istream& is, TutoringSession& session);
};

#endif // TUTORING_SESSION_H