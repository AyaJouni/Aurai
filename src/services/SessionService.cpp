#include "include/services/SessionService.h"
#include "include/utils/Logger.h"
#include <algorithm>
#include <ctime>

// Constructor
SessionService::SessionService() : nextSessionId(1)
{
    loadSessions();
}

// Destructor
SessionService::~SessionService()
{
    saveSessions();
}

// Load sessions from file
void SessionService::loadSessions()
{
    // In a real implementation, this would load from a file
    // For now, we'll create some sample sessions for testing

    // Sample session 1
    std::vector<int> aiModelIds1 = {1}; // GPT-4
    auto session1 = std::make_shared<TutoringSession>(
        1, 1, 1, // sessionId, clientId, tutorId
        aiModelIds1,
        "2025-04-25", "14:00",
        90,   // 90 minutes duration
        true, // Remote
        "Zoom");
    session1->setLearningObjectives("Introduction to GPT-4 architecture and capabilities");
    session1->setSessionCost(180.0);

    // Sample session 2
    std::vector<int> aiModelIds2 = {3}; // Claude
    auto session2 = std::make_shared<TutoringSession>(
        2, 2, 2, // sessionId, clientId, tutorId
        aiModelIds2,
        "2025-04-26", "10:00",
        120,  // 120 minutes duration
        true, // Remote
        "Microsoft Teams");
    session2->setLearningObjectives("Advanced prompting techniques for Claude AI");
    session2->setSessionCost(180.0);

    // Sample session 3 (completed session)
    std::vector<int> aiModelIds3 = {1, 2}; // GPT-4 and DALL-E
    auto session3 = std::make_shared<TutoringSession>(
        3, 1, 1, // sessionId, clientId, tutorId
        aiModelIds3,
        "2025-04-15", "09:00",
        60,    // 60 minutes duration
        false, // In-person
        "");
    session3->setStatus("Completed");
    session3->setClientRating(4.5);
    session3->setSessionNotes("Client showed good understanding of the concepts.");
    session3->setSkillsGained("Basic prompt engineering techniques");
    session3->setSessionCost(120.0);
    session3->setPaymentStatus("Paid");

    // Add sessions to collection
    sessions.push_back(session1);
    sessions.push_back(session2);
    sessions.push_back(session3);

    nextSessionId = 4; // Set next ID after sample sessions

    Logger::getInstance().info("Loaded " + std::to_string(sessions.size()) + " tutoring sessions");
}

// Save sessions to file
void SessionService::saveSessions()
{
    // In a real implementation, this would save to a file
    Logger::getInstance().info("Saved " + std::to_string(sessions.size()) + " tutoring sessions");
}

// Session management methods
bool SessionService::scheduleSession(std::shared_ptr<TutoringSession> session)
{
    // Set session ID if not already set
    if (session->getSessionId() == 0)
    {
        session->setSessionId(nextSessionId++);
    }

    // Validate date and time
    if (!isValidDate(session->getSessionDate()) || !isValidTime(session->getStartTime()))
    {
        Logger::getInstance().error("Invalid date or time format for session");
        return false;
    }

    // Check tutor availability
    if (!isTutorAvailable(session->getTutorId(),
                          session->getSessionDate(),
                          session->getStartTime(),
                          session->getDurationMinutes()))
    {
        Logger::getInstance().error("Tutor is not available at the specified time");
        return false;
    }

    // Add to collection
    sessions.push_back(session);
    saveSessions();

    Logger::getInstance().info("Scheduled new session #" +
                               std::to_string(session->getSessionId()) +
                               " for client " + std::to_string(session->getClientId()));
    return true;
}

bool SessionService::cancelSession(int sessionId, const std::string &reason)
{
    auto session = getSessionById(sessionId);
    if (!session)
    {
        return false;
    }

    session->cancelSession(reason);
    saveSessions();

    Logger::getInstance().info("Cancelled session #" + std::to_string(sessionId) +
                               ": " + reason);
    return true;
}

bool SessionService::completeSession(int sessionId, double clientRating,
                                     const std::string &notes,
                                     const std::string &skillsGained)
{
    auto session = getSessionById(sessionId);
    if (!session)
    {
        return false;
    }

    session->completeSession(clientRating, notes, skillsGained);
    saveSessions();

    Logger::getInstance().info("Completed session #" + std::to_string(sessionId) +
                               " with rating: " + std::to_string(clientRating));
    return true;
}

bool SessionService::updateSessionDetails(int sessionId, const std::string &date,
                                          const std::string &startTime, int durationMinutes)
{
    auto session = getSessionById(sessionId);
    if (!session)
    {
        return false;
    }

    // Validate date and time
    if (!isValidDate(date) || !isValidTime(startTime))
    {
        Logger::getInstance().error("Invalid date or time format for session update");
        return false;
    }

    // Check tutor availability (but skip checking the current session)
    if (date != session->getSessionDate() ||
        startTime != session->getStartTime() ||
        durationMinutes != session->getDurationMinutes())
    {

        if (!isTutorAvailable(session->getTutorId(), date, startTime, durationMinutes))
        {
            Logger::getInstance().error("Tutor is not available at the requested time");
            return false;
        }
    }

    // Update session details
    session->setSessionDate(date);
    session->setStartTime(startTime);
    session->setDurationMinutes(durationMinutes);
    saveSessions();

    Logger::getInstance().info("Updated details for session #" + std::to_string(sessionId));
    return true;
}

// Session retrieval methods
std::shared_ptr<TutoringSession> SessionService::getSessionById(int sessionId) const
{
    for (const auto &session : sessions)
    {
        if (session->getSessionId() == sessionId)
        {
            return session;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<TutoringSession>> SessionService::getAllSessions() const
{
    return sessions;
}

std::vector<std::shared_ptr<TutoringSession>> SessionService::getClientSessions(int clientId) const
{
    std::vector<std::shared_ptr<TutoringSession>> clientSessions;

    for (const auto &session : sessions)
    {
        if (session->getClientId() == clientId)
        {
            clientSessions.push_back(session);
        }
    }

    return clientSessions;
}

std::vector<std::shared_ptr<TutoringSession>> SessionService::getTutorSessions(int tutorId) const
{
    std::vector<std::shared_ptr<TutoringSession>> tutorSessions;

    for (const auto &session : sessions)
    {
        if (session->getTutorId() == tutorId)
        {
            tutorSessions.push_back(session);
        }
    }

    return tutorSessions;
}

std::vector<std::shared_ptr<TutoringSession>> SessionService::getSessionsByDate(const std::string &date) const
{
    std::vector<std::shared_ptr<TutoringSession>> dateSessions;

    for (const auto &session : sessions)
    {
        if (session->getSessionDate() == date)
        {
            dateSessions.push_back(session);
        }
    }

    return dateSessions;
}

std::vector<std::shared_ptr<TutoringSession>> SessionService::getSessionsByAIModel(int aiModelId) const
{
    std::vector<std::shared_ptr<TutoringSession>> modelSessions;

    for (const auto &session : sessions)
    {
        if (session->includesAIModel(aiModelId))
        {
            modelSessions.push_back(session);
        }
    }

    return modelSessions;
}

std::vector<std::shared_ptr<TutoringSession>> SessionService::getUpcomingSessions() const
{
    std::vector<std::shared_ptr<TutoringSession>> upcomingSessions;

    // Get current date
    time_t now = time(nullptr);
    struct tm *timeinfo = localtime(&now);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    std::string currentDate(buffer);

    for (const auto &session : sessions)
    {
        if (session->getSessionDate() >= currentDate &&
            session->getStatus() == "Scheduled")
        {
            upcomingSessions.push_back(session);
        }
    }

    return upcomingSessions;
}

std::vector<std::shared_ptr<TutoringSession>> SessionService::getCompletedSessions() const
{
    std::vector<std::shared_ptr<TutoringSession>> completedSessions;

    for (const auto &session : sessions)
    {
        if (session->getStatus() == "Completed")
        {
            completedSessions.push_back(session);
        }
    }

    return completedSessions;
}

// Session content management
bool SessionService::addSessionTopic(int sessionId, const std::string &topic)
{
    auto session = getSessionById(sessionId);
    if (!session)
    {
        return false;
    }

    session->addTopic(topic);
    saveSessions();
    return true;
}

bool SessionService::setSessionObjectives(int sessionId, const std::string &objectives)
{
    auto session = getSessionById(sessionId);
    if (!session)
    {
        return false;
    }

    session->setLearningObjectives(objectives);
    saveSessions();
    return true;
}

bool SessionService::assignSessionHomework(int sessionId, const std::string &homework)
{
    auto session = getSessionById(sessionId);
    if (!session)
    {
        return false;
    }

    session->setHomeworkAssigned(homework);
    saveSessions();
    return true;
}

// Payment management
bool SessionService::updateSessionPayment(int sessionId, double cost, const std::string &status)
{
    auto session = getSessionById(sessionId);
    if (!session)
    {
        return false;
    }

    session->setSessionCost(cost);
    session->setPaymentStatus(status);
    saveSessions();
    return true;
}

bool SessionService::markSessionAsPaid(int sessionId)
{
    auto session = getSessionById(sessionId);
    if (!session)
    {
        return false;
    }

    session->setPaymentStatus("Paid");
    saveSessions();
    return true;
}

std::vector<std::shared_ptr<TutoringSession>> SessionService::getUnpaidSessions() const
{
    std::vector<std::shared_ptr<TutoringSession>> unpaidSessions;

    for (const auto &session : sessions)
    {
        if (session->getPaymentStatus() == "Pending")
        {
            unpaidSessions.push_back(session);
        }
    }

    return unpaidSessions;
}

// Analytics methods
double SessionService::getAverageSessionRating() const
{
    double totalRating = 0.0;
    int completedCount = 0;

    for (const auto &session : sessions)
    {
        if (session->getStatus() == "Completed")
        {
            totalRating += session->getClientRating();
            completedCount++;
        }
    }

    return completedCount > 0 ? totalRating / completedCount : 0.0;
}

std::map<std::string, int> SessionService::getPopularSessionTopics() const
{
    std::map<std::string, int> topicCounts;

    for (const auto &session : sessions)
    {
        for (const auto &topic : session->getTopics())
        {
            topicCounts[topic]++;
        }
    }

    return topicCounts;
}

std::map<int, int> SessionService::getSessionsByAIModelCount() const
{
    std::map<int, int> modelCounts;

    for (const auto &session : sessions)
    {
        for (const auto &modelId : session->getAIModelIds())
        {
            modelCounts[modelId]++;
        }
    }

    return modelCounts;
}

double SessionService::getTotalRevenue(const std::string &startDate, const std::string &endDate) const
{
    double totalRevenue = 0.0;

    for (const auto &session : sessions)
    {
        if (session->getSessionDate() >= startDate &&
            session->getSessionDate() <= endDate &&
            session->getPaymentStatus() == "Paid")
        {
            totalRevenue += session->getSessionCost();
        }
    }

    return totalRevenue;
}

double SessionService::getAverageSessionDuration() const
{
    if (sessions.empty())
    {
        return 0.0;
    }

    int totalDuration = 0;
    for (const auto &session : sessions)
    {
        totalDuration += session->getDurationMinutes();
    }

    return static_cast<double>(totalDuration) / sessions.size();
}

// Private helper methods
bool SessionService::isValidDate(const std::string &date) const
{
    // Basic validation for YYYY-MM-DD format
    if (date.length() != 10)
    {
        return false;
    }

    if (date[4] != '-' || date[7] != '-')
    {
        return false;
    }

    // Make sure all other characters are digits
    for (int i = 0; i < 10; i++)
    {
        if (i != 4 && i != 7 && !isdigit(date[i]))
        {
            return false;
        }
    }

    // Check basic ranges for year, month, day
    int year = std::stoi(date.substr(0, 4));
    int month = std::stoi(date.substr(5, 2));
    int day = std::stoi(date.substr(8, 2));

    if (year < 2023 || year > 2030)
    { // Arbitrary range
        return false;
    }

    if (month < 1 || month > 12)
    {
        return false;
    }

    if (day < 1 || day > 31)
    {
        return false;
    }

    return true;
}

bool SessionService::isValidTime(const std::string &time) const
{
    // Basic validation for HH:MM format
    if (time.length() != 5)
    {
        return false;
    }

    if (time[2] != ':')
    {
        return false;
    }

    // Make sure all other characters are digits
    for (int i = 0; i < 5; i++)
    {
        if (i != 2 && !isdigit(time[i]))
        {
            return false;
        }
    }

    // Check ranges for hours and minutes
    int hours = std::stoi(time.substr(0, 2));
    int minutes = std::stoi(time.substr(3, 2));

    if (hours < 0 || hours > 23)
    {
        return false;
    }

    if (minutes < 0 || minutes > 59)
    {
        return false;
    }

    return true;
}

bool SessionService::isTutorAvailable(int tutorId, const std::string &date,
                                      const std::string &startTime, int durationMinutes) const
{
    // Convert the new session's time to minutes since midnight
    int newStartMinutes = (std::stoi(startTime.substr(0, 2)) * 60) +
                          std::stoi(startTime.substr(3, 2));
    int newEndMinutes = newStartMinutes + durationMinutes;

    // Loop through all existing sessions
    for (const auto &existingSession : sessions)
    {
        // Skip sessions for other tutors
        if (existingSession->getTutorId() != tutorId)
        {
            continue;
        }

        // Skip cancelled sessions
        if (existingSession->getStatus() == "Cancelled")
        {
            continue;
        }

        // If the session is on the same date, check for time conflicts
        if (existingSession->getSessionDate() == date)
        {
            // Convert existing session time to minutes
            int existingStartMinutes = (std::stoi(existingSession->getStartTime().substr(0, 2)) * 60) +
                                       std::stoi(existingSession->getStartTime().substr(3, 2));
            int existingEndMinutes = existingStartMinutes + existingSession->getDurationMinutes();

            // Check for overlap:
            // New session starts before existing ends AND new session ends after existing starts
            if (newStartMinutes < existingEndMinutes && newEndMinutes > existingStartMinutes)
            {
                return false; // Time conflict
            }
        }
    }

    return true; // No conflicts
}