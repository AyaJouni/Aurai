#include "include/services/TutorService.h"
#include "include/utils/Logger.h"
#include "include/utils/Exception.h"
#include "include/utils/Validation.h"
#include <algorithm>
#include <iostream>

// Constructor
TutorService::TutorService()
{
    loadTutors();
}

// Destructor
TutorService::~TutorService()
{
    saveTutors();
}

// Load tutors from file/database
void TutorService::loadTutors()
{
    // In a real implementation with database integration, this would load from db
    // For now, we'll create some sample tutors

    // Define AI specializations
    std::vector<std::string> aiSpecializations1 = {"GPT-4", "DALL-E", "Claude AI"};
    std::vector<std::string> aiSpecializations2 = {"Claude AI", "LLaMA"};
    std::vector<std::string> aiSpecializations3 = {"Midjourney", "Stable Diffusion"};

    // Define domain expertise
    std::vector<std::string> domainExpertise1 = {"Natural Language Processing", "Neural Networks"};
    std::vector<std::string> domainExpertise2 = {"Large Language Models", "Prompt Engineering"};
    std::vector<std::string> domainExpertise3 = {"Generative Art", "Computer Vision"};

    // Create tutors
    auto tutor1 = std::make_shared<Tutor>(
        1, "ejohnson", "password",
        "Emily", "Johnson",
        "emily.johnson@aitutoring.com", "555-111-2222",
        aiSpecializations1, domainExpertise1,
        "PhD in Computer Science", 5, 120.0);
    tutor1->setAIModelExperience("GPT-4", 5);
    tutor1->setAIModelExperience("DALL-E", 4);
    tutor1->setAIModelExperience("Claude AI", 4);
    tutor1->setSessionsCompleted(32);
    tutor1->updateRating(4.8);

    auto tutor2 = std::make_shared<Tutor>(
        2, "mlee", "password",
        "Michael", "Lee",
        "michael.lee@aitutoring.com", "555-333-4444",
        aiSpecializations2, domainExpertise2,
        "MS in AI", 3, 90.0);
    tutor2->setAIModelExperience("Claude AI", 5);
    tutor2->setAIModelExperience("LLaMA", 3);
    tutor2->setSessionsCompleted(15);
    tutor2->updateRating(4.5);

    auto tutor3 = std::make_shared<Tutor>(
        3, "jwilson", "password",
        "James", "Wilson",
        "james.wilson@aitutoring.com", "555-555-6666",
        aiSpecializations3, domainExpertise3,
        "BS in Computer Science", 4, 100.0);
    tutor3->setAIModelExperience("Midjourney", 5);
    tutor3->setAIModelExperience("Stable Diffusion", 5);
    tutor3->setSessionsCompleted(24);
    tutor3->updateRating(4.7);

    // Add tutors to collection
    tutors.push_back(tutor1);
    tutors.push_back(tutor2);
    tutors.push_back(tutor3);

    Logger::getInstance().info("Loaded " + std::to_string(tutors.size()) + " tutors");
}

// Save tutors to file/database
void TutorService::saveTutors()
{
    // In a real implementation, this would save to database
    Logger::getInstance().info("Saved " + std::to_string(tutors.size()) + " tutors");
}

// Tutor retrieval methods
std::shared_ptr<Tutor> TutorService::getTutorById(int tutorId) const
{
    for (const auto &tutor : tutors)
    {
        if (tutor->getUserId() == tutorId)
        {
            return tutor;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<Tutor>> TutorService::getAllTutors() const
{
    return tutors;
}

// Expertise management
bool TutorService::addTutorSpecialization(int tutorId, const std::string &aiModel)
{
    auto tutor = getTutorById(tutorId);
    if (!tutor)
    {
        return false;
    }

    tutor->addAISpecialization(aiModel);
    saveTutors();

    Logger::getInstance().info("Added AI specialization '" + aiModel + "' for tutor: " + tutor->getFullName());
    return true;
}

bool TutorService::removeTutorSpecialization(int tutorId, const std::string &aiModel)
{
    auto tutor = getTutorById(tutorId);
    if (!tutor)
    {
        return false;
    }

    tutor->removeAISpecialization(aiModel);
    saveTutors();

    Logger::getInstance().info("Removed AI specialization '" + aiModel + "' for tutor: " + tutor->getFullName());
    return true;
}

bool TutorService::addTutorDomainExpertise(int tutorId, const std::string &domain)
{
    auto tutor = getTutorById(tutorId);
    if (!tutor)
    {
        return false;
    }

    tutor->addDomainExpertise(domain);
    saveTutors();

    Logger::getInstance().info("Added domain expertise '" + domain + "' for tutor: " + tutor->getFullName());
    return true;
}

bool TutorService::removeTutorDomainExpertise(int tutorId, const std::string &domain)
{
    auto tutor = getTutorById(tutorId);
    if (!tutor)
    {
        return false;
    }

    tutor->removeDomainExpertise(domain);
    saveTutors();

    Logger::getInstance().info("Removed domain expertise '" + domain + "' for tutor: " + tutor->getFullName());
    return true;
}

// AI Model experience
bool TutorService::updateTutorModelExperience(int tutorId, const std::string &aiModel, int experienceLevel)
{
    auto tutor = getTutorById(tutorId);
    if (!tutor)
    {
        return false;
    }

    tutor->setAIModelExperience(aiModel, experienceLevel);
    saveTutors();

    Logger::getInstance().info("Updated experience level for tutor " + tutor->getFullName() +
                               " on " + aiModel + " to level " + std::to_string(experienceLevel));
    return true;
}

std::map<std::string, int> TutorService::getTutorModelExperience(int tutorId) const
{
    auto tutor = getTutorById(tutorId);
    if (!tutor)
    {
        return {};
    }

    return tutor->getAllAIModelExperience();
}

// Tutor search methods
std::vector<std::shared_ptr<Tutor>> TutorService::getTutorsBySpecialization(const std::string &aiModel) const
{
    std::vector<std::shared_ptr<Tutor>> results;

    for (const auto &tutor : tutors)
    {
        if (tutor->hasAISpecialization(aiModel))
        {
            results.push_back(tutor);
        }
    }

    return results;
}

std::vector<std::shared_ptr<Tutor>> TutorService::getTutorsByDomain(const std::string &domain) const
{
    std::vector<std::shared_ptr<Tutor>> results;

    for (const auto &tutor : tutors)
    {
        if (tutor->hasDomainExpertise(domain))
        {
            results.push_back(tutor);
        }
    }

    return results;
}

std::vector<std::shared_ptr<Tutor>> TutorService::getTutorsByExperience(int minYearsExperience) const
{
    std::vector<std::shared_ptr<Tutor>> results;

    for (const auto &tutor : tutors)
    {
        if (tutor->getExperienceYears() >= minYearsExperience)
        {
            results.push_back(tutor);
        }
    }

    return results;
}

// Tutor rating management
bool TutorService::updateTutorRating(int tutorId, double newRating)
{
    auto tutor = getTutorById(tutorId);
    if (!tutor)
    {
        return false;
    }

    tutor->updateRating(newRating);
    saveTutors();

    Logger::getInstance().info("Updated rating for tutor " + tutor->getFullName() +
                               " to " + std::to_string(newRating));
    return true;
}

double TutorService::getTutorAverageRating(int tutorId) const
{
    auto tutor = getTutorById(tutorId);
    if (!tutor)
    {
        return 0.0;
    }

    return tutor->getAverageRating();
}

// Tutor session management
bool TutorService::incrementTutorSessions(int tutorId)
{
    auto tutor = getTutorById(tutorId);
    if (!tutor)
    {
        return false;
    }

    tutor->incrementSessionsCompleted();
    saveTutors();

    Logger::getInstance().info("Incremented session count for tutor " + tutor->getFullName() +
                               " to " + std::to_string(tutor->getSessionsCompleted()));
    return true;
}

int TutorService::getTutorCompletedSessions(int tutorId) const
{
    auto tutor = getTutorById(tutorId);
    if (!tutor)
    {
        return 0;
    }

    return tutor->getSessionsCompleted();
}

// Rate management
bool TutorService::updateTutorRate(int tutorId, double hourlyRate)
{
    auto tutor = getTutorById(tutorId);
    if (!tutor)
    {
        return false;
    }

    tutor->setHourlyRate(hourlyRate);
    saveTutors();

    Logger::getInstance().info("Updated hourly rate for tutor " + tutor->getFullName() +
                               " to $" + std::to_string(hourlyRate));
    return true;
}

double TutorService::getTutorRate(int tutorId) const
{
    auto tutor = getTutorById(tutorId);
    if (!tutor)
    {
        return 0.0;
    }

    return tutor->getHourlyRate();
}

// Analytics methods
std::map<std::string, int> TutorService::getPopularSpecializations() const
{
    std::map<std::string, int> specializationCounts;

    for (const auto &tutor : tutors)
    {
        const auto &specializations = tutor->getAISpecializations();
        for (const auto &specialization : specializations)
        {
            specializationCounts[specialization]++;
        }
    }

    return specializationCounts;
}

std::vector<std::shared_ptr<Tutor>> TutorService::getTopRatedTutors(int count) const
{
    auto sortedTutors = tutors;

    std::sort(sortedTutors.begin(), sortedTutors.end(),
              [](const std::shared_ptr<Tutor> &a, const std::shared_ptr<Tutor> &b)
              {
                  return a->getAverageRating() > b->getAverageRating();
              });

    int resultCount = std::min(static_cast<int>(sortedTutors.size()), count);
    return std::vector<std::shared_ptr<Tutor>>(sortedTutors.begin(), sortedTutors.begin() + resultCount);
}

std::vector<std::shared_ptr<Tutor>> TutorService::getMostExperiencedTutors(int count) const
{
    auto sortedTutors = tutors;

    std::sort(sortedTutors.begin(), sortedTutors.end(),
              [](const std::shared_ptr<Tutor> &a, const std::shared_ptr<Tutor> &b)
              {
                  return a->getExperienceYears() > b->getExperienceYears();
              });

    int resultCount = std::min(static_cast<int>(sortedTutors.size()), count);
    return std::vector<std::shared_ptr<Tutor>>(sortedTutors.begin(), sortedTutors.begin() + resultCount);
}

// Matching algorithms
std::vector<std::shared_ptr<Tutor>> TutorService::findMatchingTutorsForClient(
    int clientId, const std::vector<std::string> &aiModels) const
{

    std::vector<std::shared_ptr<Tutor>> matchingTutors;

    for (const auto &tutor : tutors)
    {
        // Check if tutor has at least one of the requested AI model specializations
        for (const auto &model : aiModels)
        {
            if (tutor->hasAISpecialization(model))
            {
                matchingTutors.push_back(tutor);
                break;
            }
        }
    }

    // Sort matching tutors by average rating
    std::sort(matchingTutors.begin(), matchingTutors.end(),
              [](const std::shared_ptr<Tutor> &a, const std::shared_ptr<Tutor> &b)
              {
                  return a->getAverageRating() > b->getAverageRating();
              });

    return matchingTutors;
}

std::shared_ptr<Tutor> TutorService::getBestTutorMatch(int clientId, const std::string &aiModel) const
{
    std::vector<std::shared_ptr<Tutor>> matchingTutors;

    for (const auto &tutor : tutors)
    {
        if (tutor->hasAISpecialization(aiModel))
        {
            matchingTutors.push_back(tutor);
        }
    }

    if (matchingTutors.empty())
    {
        return nullptr;
    }

    // Sort matching tutors by experience level with the specific AI model
    std::sort(matchingTutors.begin(), matchingTutors.end(),
              [aiModel](const std::shared_ptr<Tutor> &a, const std::shared_ptr<Tutor> &b)
              {
                  return a->getAIModelExperience(aiModel) > b->getAIModelExperience(aiModel);
              });

    return matchingTutors[0];
}