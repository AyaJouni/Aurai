#include "include/models/TutoringSession.h"
#include <algorithm>
#include <iomanip>
#include <sstream>

// Default constructor
TutoringSession::TutoringSession()
    : sessionId(0), clientId(0), tutorId(0), aiModelIds(), sessionDate(""),
      startTime(""), durationMinutes(0), status("Scheduled"), clientRating(0.0),
      learningObjectives(""), sessionNotes(""), topics(), skillsGained(""),
      homeworkAssigned(""), sessionCost(0.0), paymentStatus("Pending"),
      isRemote(true), platform("") {}

// Parameterized constructor
TutoringSession::TutoringSession(int sessionId, int clientId, int tutorId,
                                 const std::vector<int> &aiModelIds,
                                 const std::string &sessionDate, const std::string &startTime,
                                 int durationMinutes, bool isRemote,
                                 const std::string &platform)
    : sessionId(sessionId), clientId(clientId), tutorId(tutorId),
      aiModelIds(aiModelIds), sessionDate(sessionDate), startTime(startTime),
      durationMinutes(durationMinutes), status("Scheduled"), clientRating(0.0),
      learningObjectives(""), sessionNotes(""), topics(), skillsGained(""),
      homeworkAssigned(""), sessionCost(0.0), paymentStatus("Pending"),
      isRemote(isRemote), platform(platform) {}

// Getters and setters
int TutoringSession::getSessionId() const
{
    return sessionId;
}

void TutoringSession::setSessionId(int id)
{
    sessionId = id;
}

int TutoringSession::getClientId() const
{
    return clientId;
}

void TutoringSession::setClientId(int id)
{
    clientId = id;
}

int TutoringSession::getTutorId() const
{
    return tutorId;
}

void TutoringSession::setTutorId(int id)
{
    tutorId = id;
}

const std::vector<int> &TutoringSession::getAIModelIds() const
{
    return aiModelIds;
}

void TutoringSession::addAIModel(int modelId)
{
    // Check if the model is already in the list
    if (!includesAIModel(modelId))
    {
        aiModelIds.push_back(modelId);
    }
}

void TutoringSession::removeAIModel(int modelId)
{
    auto it = std::find(aiModelIds.begin(), aiModelIds.end(), modelId);
    if (it != aiModelIds.end())
    {
        aiModelIds.erase(it);
    }
}

bool TutoringSession::includesAIModel(int modelId) const
{
    return std::find(aiModelIds.begin(), aiModelIds.end(), modelId) != aiModelIds.end();
}

std::string TutoringSession::getSessionDate() const
{
    return sessionDate;
}

void TutoringSession::setSessionDate(const std::string &date)
{
    sessionDate = date;
}

std::string TutoringSession::getStartTime() const
{
    return startTime;
}

void TutoringSession::setStartTime(const std::string &time)
{
    startTime = time;
}

int TutoringSession::getDurationMinutes() const
{
    return durationMinutes;
}

void TutoringSession::setDurationMinutes(int duration)
{
    durationMinutes = duration;
}

std::string TutoringSession::getStatus() const
{
    return status;
}

void TutoringSession::setStatus(const std::string &status)
{
    this->status = status;
}

double TutoringSession::getClientRating() const
{
    return clientRating;
}

void TutoringSession::setClientRating(double rating)
{
    // Ensure rating is between 0 and 5
    if (rating >= 0 && rating <= 5)
    {
        clientRating = rating;
    }
}

std::string TutoringSession::getLearningObjectives() const
{
    return learningObjectives;
}

void TutoringSession::setLearningObjectives(const std::string &objectives)
{
    learningObjectives = objectives;
}

std::string TutoringSession::getSessionNotes() const
{
    return sessionNotes;
}

void TutoringSession::setSessionNotes(const std::string &notes)
{
    sessionNotes = notes;
}

const std::vector<std::string> &TutoringSession::getTopics() const
{
    return topics;
}

void TutoringSession::addTopic(const std::string &topic)
{
    // Check if the topic is already in the list
    auto it = std::find(topics.begin(), topics.end(), topic);
    if (it == topics.end())
    {
        topics.push_back(topic);
    }
}

void TutoringSession::removeTopic(const std::string &topic)
{
    auto it = std::find(topics.begin(), topics.end(), topic);
    if (it != topics.end())
    {
        topics.erase(it);
    }
}

std::string TutoringSession::getSkillsGained() const
{
    return skillsGained;
}

void TutoringSession::setSkillsGained(const std::string &skills)
{
    skillsGained = skills;
}

std::string TutoringSession::getHomeworkAssigned() const
{
    return homeworkAssigned;
}

void TutoringSession::setHomeworkAssigned(const std::string &homework)
{
    homeworkAssigned = homework;
}

double TutoringSession::getSessionCost() const
{
    return sessionCost;
}

void TutoringSession::setSessionCost(double cost)
{
    sessionCost = cost;
}

std::string TutoringSession::getPaymentStatus() const
{
    return paymentStatus;
}

void TutoringSession::setPaymentStatus(const std::string &status)
{
    paymentStatus = status;
}

bool TutoringSession::getIsRemote() const
{
    return isRemote;
}

void TutoringSession::setIsRemote(bool remote)
{
    isRemote = remote;
}

std::string TutoringSession::getPlatform() const
{
    return platform;
}

void TutoringSession::setPlatform(const std::string &platform)
{
    this->platform = platform;
}

// Utility methods
void TutoringSession::completeSession(double rating, const std::string &notes,
                                      const std::string &skillsGained)
{
    setStatus("Completed");
    setClientRating(rating);
    setSessionNotes(notes);
    setSkillsGained(skillsGained);
}

void TutoringSession::cancelSession(const std::string &reason)
{
    setStatus("Cancelled");
    setSessionNotes(reason);

    // If already paid, mark as refunded
    if (paymentStatus == "Paid")
    {
        setPaymentStatus("Refunded");
    }
}

std::string TutoringSession::getFormattedDuration() const
{
    int hours = durationMinutes / 60;
    int minutes = durationMinutes % 60;

    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << hours << ":"
       << std::setw(2) << std::setfill('0') << minutes;

    return ss.str();
}

// Display methods
void TutoringSession::displayInfo() const
{
    std::cout << "Session ID: " << sessionId << std::endl;
    std::cout << "Client ID: " << clientId << std::endl;
    std::cout << "Tutor ID: " << tutorId << std::endl;
    std::cout << "Date: " << sessionDate << std::endl;
    std::cout << "Time: " << startTime << " (" << getFormattedDuration() << " duration)" << std::endl;
    std::cout << "Status: " << status << std::endl;

    if (status == "Completed")
    {
        std::cout << "Rating: " << clientRating << "/5" << std::endl;
    }

    std::cout << "Location: " << (isRemote ? "Remote" : "In-person") << std::endl;

    if (isRemote && !platform.empty())
    {
        std::cout << "Platform: " << platform << std::endl;
    }

    std::cout << "Cost: $" << std::fixed << std::setprecision(2) << sessionCost << std::endl;
    std::cout << "Payment Status: " << paymentStatus << std::endl;

    if (!learningObjectives.empty())
    {
        std::cout << "\nLearning Objectives: " << learningObjectives << std::endl;
    }

    if (!sessionNotes.empty())
    {
        std::cout << "\nSession Notes: " << sessionNotes << std::endl;
    }

    if (!skillsGained.empty())
    {
        std::cout << "\nSkills Gained: " << skillsGained << std::endl;
    }

    if (!homeworkAssigned.empty())
    {
        std::cout << "\nHomework: " << homeworkAssigned << std::endl;
    }

    // Display AI models if available
    if (!aiModelIds.empty())
    {
        std::cout << "\nAI Models Covered: ";
        for (size_t i = 0; i < aiModelIds.size(); ++i)
        {
            std::cout << aiModelIds[i];
            if (i < aiModelIds.size() - 1)
            {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
}

void TutoringSession::displayTopics() const
{
    std::cout << "Topics Covered in Session #" << sessionId << ":" << std::endl;

    if (topics.empty())
    {
        std::cout << "  No topics recorded" << std::endl;
    }
    else
    {
        for (const auto &topic : topics)
        {
            std::cout << "  - " << topic << std::endl;
        }
    }
}

// Operator overloading
std::ostream &operator<<(std::ostream &os, const TutoringSession &session)
{
    os << "Session ID: " << session.sessionId << std::endl;
    os << "Date & Time: " << session.sessionDate << " at " << session.startTime << std::endl;
    os << "Duration: " << session.getFormattedDuration() << std::endl;
    os << "Status: " << session.status << std::endl;
    os << "Client ID: " << session.clientId << std::endl;
    os << "Tutor ID: " << session.tutorId << std::endl;

    return os;
}

std::istream &operator>>(std::istream &is, TutoringSession &session)
{
    std::cout << "Enter Session ID: ";
    is >> session.sessionId;
    is.ignore(); // Clear newline

    std::cout << "Enter Client ID: ";
    is >> session.clientId;
    is.ignore(); // Clear newline

    std::cout << "Enter Tutor ID: ";
    is >> session.tutorId;
    is.ignore(); // Clear newline

    std::cout << "Enter Session Date (YYYY-MM-DD): ";
    std::getline(is, session.sessionDate);

    std::cout << "Enter Start Time (HH:MM): ";
    std::getline(is, session.startTime);

    std::cout << "Enter Duration (minutes): ";
    is >> session.durationMinutes;
    is.ignore(); // Clear newline

    std::cout << "Is Remote Session? (y/n): ";
    std::string remoteInput;
    std::getline(is, remoteInput);
    session.isRemote = (remoteInput == "y" || remoteInput == "Y");

    if (session.isRemote)
    {
        std::cout << "Enter Platform: ";
        std::getline(is, session.platform);
    }

    std::cout << "Enter Session Cost: $";
    is >> session.sessionCost;
    is.ignore(); // Clear newline

    // Set default values for other fields
    session.status = "Scheduled";
    session.paymentStatus = "Pending";

    return is;
}