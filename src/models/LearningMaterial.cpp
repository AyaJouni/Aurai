#include "include/models/LearningMaterial.h"
#include <algorithm>
#include <iomanip>
#include <sstream>

// Default constructor
LearningMaterial::LearningMaterial()
    : materialId(0), title(""), description(""), type(""), format(""), author(""),
      creationDate(""), aiModelIds(), tags(), difficultyLevel(1), url(""),
      localPath(""), estimatedTimeMinutes(0), rating(0.0), usageCount(0) {}

// Parameterized constructor
LearningMaterial::LearningMaterial(int materialId, const std::string &title,
                                   const std::string &description, const std::string &type,
                                   const std::string &format, const std::string &author)
    : materialId(materialId), title(title), description(description), type(type),
      format(format), author(author), creationDate(""), aiModelIds(), tags(),
      difficultyLevel(1), url(""), localPath(""), estimatedTimeMinutes(0),
      rating(0.0), usageCount(0) {}

// Getters and setters
int LearningMaterial::getMaterialId() const
{
    return materialId;
}

void LearningMaterial::setMaterialId(int id)
{
    materialId = id;
}

std::string LearningMaterial::getTitle() const
{
    return title;
}

void LearningMaterial::setTitle(const std::string &title)
{
    this->title = title;
}

std::string LearningMaterial::getDescription() const
{
    return description;
}

void LearningMaterial::setDescription(const std::string &description)
{
    this->description = description;
}

std::string LearningMaterial::getType() const
{
    return type;
}

void LearningMaterial::setType(const std::string &type)
{
    this->type = type;
}

std::string LearningMaterial::getFormat() const
{
    return format;
}

void LearningMaterial::setFormat(const std::string &format)
{
    this->format = format;
}

std::string LearningMaterial::getAuthor() const
{
    return author;
}

void LearningMaterial::setAuthor(const std::string &author)
{
    this->author = author;
}

std::string LearningMaterial::getCreationDate() const
{
    return creationDate;
}

void LearningMaterial::setCreationDate(const std::string &date)
{
    creationDate = date;
}

const std::vector<int> &LearningMaterial::getAIModelIds() const
{
    return aiModelIds;
}

void LearningMaterial::addAIModel(int modelId)
{
    // Check if the model ID is already in the list
    if (std::find(aiModelIds.begin(), aiModelIds.end(), modelId) == aiModelIds.end())
    {
        aiModelIds.push_back(modelId);
    }
}

void LearningMaterial::removeAIModel(int modelId)
{
    aiModelIds.erase(
        std::remove(aiModelIds.begin(), aiModelIds.end(), modelId),
        aiModelIds.end());
}

bool LearningMaterial::isRelevantForModel(int modelId) const
{
    return std::find(aiModelIds.begin(), aiModelIds.end(), modelId) != aiModelIds.end();
}

const std::vector<std::string> &LearningMaterial::getTags() const
{
    return tags;
}

void LearningMaterial::addTag(const std::string &tag)
{
    // Check if the tag is already in the list
    if (std::find(tags.begin(), tags.end(), tag) == tags.end())
    {
        tags.push_back(tag);
    }
}

void LearningMaterial::removeTag(const std::string &tag)
{
    tags.erase(
        std::remove(tags.begin(), tags.end(), tag),
        tags.end());
}

bool LearningMaterial::hasTag(const std::string &tag) const
{
    return std::find(tags.begin(), tags.end(), tag) != tags.end();
}

int LearningMaterial::getDifficultyLevel() const
{
    return difficultyLevel;
}

void LearningMaterial::setDifficultyLevel(int level)
{
    if (level >= 1 && level <= 5)
    {
        difficultyLevel = level;
    }
}

std::string LearningMaterial::getURL() const
{
    return url;
}

void LearningMaterial::setURL(const std::string &url)
{
    this->url = url;
}

std::string LearningMaterial::getLocalPath() const
{
    return localPath;
}

void LearningMaterial::setLocalPath(const std::string &path)
{
    localPath = path;
}

int LearningMaterial::getEstimatedTimeMinutes() const
{
    return estimatedTimeMinutes;
}

void LearningMaterial::setEstimatedTimeMinutes(int minutes)
{
    if (minutes >= 0)
    {
        estimatedTimeMinutes = minutes;
    }
}

double LearningMaterial::getRating() const
{
    return rating;
}

void LearningMaterial::updateRating(double newRating)
{
    if (newRating >= 0.0 && newRating <= 5.0)
    {
        // Simple update for now, in a real system might need to track number of ratings
        rating = newRating;
    }
}

int LearningMaterial::getUsageCount() const
{
    return usageCount;
}

void LearningMaterial::incrementUsageCount()
{
    usageCount++;
}

void LearningMaterial::setUsageCount(int count)
{
    if (count >= 0)
    {
        usageCount = count;
    }
}

// Utility methods
std::string LearningMaterial::getDifficultyDescription() const
{
    switch (difficultyLevel)
    {
    case 1:
        return "Beginner";
    case 2:
        return "Easy";
    case 3:
        return "Intermediate";
    case 4:
        return "Advanced";
    case 5:
        return "Expert";
    default:
        return "Unknown";
    }
}

std::string LearningMaterial::getFormattedEstimatedTime() const
{
    int hours = estimatedTimeMinutes / 60;
    int minutes = estimatedTimeMinutes % 60;

    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << hours << ":"
       << std::setfill('0') << std::setw(2) << minutes;
    return ss.str();
}

bool LearningMaterial::isDigital() const
{
    // Check if the material is in a digital format
    // This is a simple implementation, can be expanded
    return !localPath.empty() || !url.empty();
}

// Display material info
void LearningMaterial::displayInfo() const
{
    std::cout << "===== Learning Material =====" << std::endl;
    std::cout << "ID: " << materialId << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Author: " << author << std::endl;
    std::cout << "Type: " << type << " (" << format << ")" << std::endl;
    std::cout << "Difficulty: " << getDifficultyDescription() << " (" << difficultyLevel << "/5)" << std::endl;
    std::cout << "Estimated Time: " << getFormattedEstimatedTime() << " (" << estimatedTimeMinutes << " min)" << std::endl;

    if (!description.empty())
    {
        std::cout << "\nDescription: " << description << std::endl;
    }

    if (!creationDate.empty())
    {
        std::cout << "Created on: " << creationDate << std::endl;
    }

    if (!url.empty())
    {
        std::cout << "URL: " << url << std::endl;
    }

    if (!localPath.empty())
    {
        std::cout << "Local Path: " << localPath << std::endl;
    }

    std::cout << "Rating: " << std::fixed << std::setprecision(1) << rating << "/5.0" << std::endl;
    std::cout << "Usage Count: " << usageCount << std::endl;

    if (!aiModelIds.empty())
    {
        std::cout << "\nAssociated AI Models: ";
        for (size_t i = 0; i < aiModelIds.size(); ++i)
        {
            std::cout << aiModelIds[i];
            if (i < aiModelIds.size() - 1)
                std::cout << ", ";
        }
        std::cout << std::endl;
    }

    displayTags();
}

void LearningMaterial::displayTags() const
{
    if (!tags.empty())
    {
        std::cout << "Tags: ";
        for (size_t i = 0; i < tags.size(); ++i)
        {
            std::cout << tags[i];
            if (i < tags.size() - 1)
                std::cout << ", ";
        }
        std::cout << std::endl;
    }
}

// Operator overloading
std::ostream &operator<<(std::ostream &os, const LearningMaterial &material)
{
    os << "Material: " << material.title << " (ID: " << material.materialId << ")" << std::endl;
    os << "Type: " << material.type << " (" << material.format << ")" << std::endl;
    os << "Author: " << material.author << std::endl;
    os << "Difficulty: " << material.getDifficultyDescription() << std::endl;
    os << "Estimated Time: " << material.getFormattedEstimatedTime() << std::endl;

    return os;
}

std::istream &operator>>(std::istream &is, LearningMaterial &material)
{
    std::cout << "Enter Material ID: ";
    is >> material.materialId;
    is.ignore(); // Clear the newline character

    std::cout << "Enter Title: ";
    std::getline(is, material.title);

    std::cout << "Enter Description: ";
    std::getline(is, material.description);

    std::cout << "Enter Type (Document, Video, Interactive, Exercise, etc.): ";
    std::getline(is, material.type);

    std::cout << "Enter Format (PDF, MP4, Notebook, etc.): ";
    std::getline(is, material.format);

    std::cout << "Enter Author: ";
    std::getline(is, material.author);

    std::cout << "Enter Creation Date (YYYY-MM-DD): ";
    std::getline(is, material.creationDate);

    std::cout << "Enter Difficulty Level (1-5): ";
    is >> material.difficultyLevel;

    std::cout << "Enter Estimated Time (in minutes): ";
    is >> material.estimatedTimeMinutes;

    is.ignore(); // Clear the newline character

    std::cout << "Enter URL (if applicable): ";
    std::getline(is, material.url);

    std::cout << "Enter Local Path (if applicable): ";
    std::getline(is, material.localPath);

    return is;
}