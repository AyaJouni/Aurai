#include "include/models/AIModel.h"
#include <algorithm>
#include <iostream>
#include <sstream>

// Default constructor
AIModel::AIModel() 
    : modelId(0), name(""), version(""), developer(""), category(""),
      releaseDate(""), description(""), capabilities(), limitations(),
      useCases(), parameters(), complexityLevel(1), popularityRank(0),
      tutorsAvailable(0), documentationURL(""), isDeprecated(false) {}

// Parameterized constructor
AIModel::AIModel(int modelId, const std::string& name, const std::string& version,
                 const std::string& developer, const std::string& category,
                 const std::string& releaseDate, const std::string& description,
                 int complexityLevel)
    : modelId(modelId), name(name), version(version), developer(developer),
      category(category), releaseDate(releaseDate), description(description),
      capabilities(), limitations(), useCases(), parameters(),
      complexityLevel(complexityLevel), popularityRank(0), tutorsAvailable(0),
      documentationURL(""), isDeprecated(false) {}

// Getters and setters
int AIModel::getModelId() const { return modelId; }
void AIModel::setModelId(int id) { modelId = id; }

std::string AIModel::getName() const { return name; }
void AIModel::setName(const std::string& name) { this->name = name; }

std::string AIModel::getVersion() const { return version; }
void AIModel::setVersion(const std::string& version) { this->version = version; }

std::string AIModel::getDeveloper() const { return developer; }
void AIModel::setDeveloper(const std::string& developer) { this->developer = developer; }

std::string AIModel::getCategory() const { return category; }
void AIModel::setCategory(const std::string& category) { this->category = category; }

std::string AIModel::getReleaseDate() const { return releaseDate; }
void AIModel::setReleaseDate(const std::string& date) { releaseDate = date; }

std::string AIModel::getDescription() const { return description; }
void AIModel::setDescription(const std::string& description) { this->description = description; }

// Capabilities methods
const std::vector<std::string>& AIModel::getCapabilities() const { return capabilities; }

void AIModel::addCapability(const std::string& capability) {
    capabilities.push_back(capability);
}

void AIModel::removeCapability(const std::string& capability) {
    auto it = std::find(capabilities.begin(), capabilities.end(), capability);
    if (it != capabilities.end()) {
        capabilities.erase(it);
    }
}

// Limitations methods
const std::vector<std::string>& AIModel::getLimitations() const { return limitations; }

void AIModel::addLimitation(const std::string& limitation) {
    limitations.push_back(limitation);
}

void AIModel::removeLimitation(const std::string& limitation) {
    auto it = std::find(limitations.begin(), limitations.end(), limitation);
    if (it != limitations.end()) {
        limitations.erase(it);
    }
}

// Use cases methods
const std::vector<std::string>& AIModel::getUseCases() const { return useCases; }

void AIModel::addUseCase(const std::string& useCase) {
    useCases.push_back(useCase);
}

void AIModel::removeUseCase(const std::string& useCase) {
    auto it = std::find(useCases.begin(), useCases.end(), useCase);
    if (it != useCases.end()) {
        useCases.erase(it);
    }
}

// Parameters methods
const std::map<std::string, std::string>& AIModel::getParameters() const { return parameters; }

void AIModel::addParameter(const std::string& param, const std::string& description) {
    parameters[param] = description;
}

void AIModel::removeParameter(const std::string& param) {
    parameters.erase(param);
}

std::string AIModel::getParameterDescription(const std::string& param) const {
    auto it = parameters.find(param);
    if (it != parameters.end()) {
        return it->second;
    }
    return "";
}

// Other getters and setters
int AIModel::getComplexityLevel() const { return complexityLevel; }
void AIModel::setComplexityLevel(int level) { 
    if (level >= 1 && level <= 5) {
        complexityLevel = level;
    }
}

int AIModel::getPopularityRank() const { return popularityRank; }
void AIModel::setPopularityRank(int rank) { popularityRank = rank; }

int AIModel::getTutorsAvailable() const { return tutorsAvailable; }
void AIModel::setTutorsAvailable(int count) { tutorsAvailable = count; }
void AIModel::incrementTutorsAvailable() { tutorsAvailable++; }
void AIModel::decrementTutorsAvailable() { 
    if (tutorsAvailable > 0) {
        tutorsAvailable--; 
    }
}

std::string AIModel::getDocumentationURL() const { return documentationURL; }
void AIModel::setDocumentationURL(const std::string& url) { documentationURL = url; }

bool AIModel::getIsDeprecated() const { return isDeprecated; }
void AIModel::setIsDeprecated(bool deprecated) { isDeprecated = deprecated; }

// Utility methods
std::string AIModel::getComplexityDescription() const {
    switch (complexityLevel) {
        case 1: return "Beginner";
        case 2: return "Easy";
        case 3: return "Intermediate";
        case 4: return "Advanced";
        case 5: return "Expert";
        default: return "Unknown";
    }
}

bool AIModel::hasCapability(const std::string& capability) const {
    return std::find(capabilities.begin(), capabilities.end(), capability) != capabilities.end();
}

bool AIModel::isCompatibleWith(const std::string& otherModelName) const {
    // Stub implementation - in a real system, this would check compatibility rules
    // For now, we'll just return true if they're from the same developer
    return true;
}

// Display methods
void AIModel::displayInfo() const {
    std::cout << "AI Model: " << name << " (v" << version << ")" << std::endl;
    std::cout << "Developer: " << developer << std::endl;
    std::cout << "Category: " << category << std::endl;
    std::cout << "Release Date: " << releaseDate << std::endl;
    std::cout << "Complexity: " << getComplexityDescription() << " (" << complexityLevel << "/5)" << std::endl;
    std::cout << "Popularity Rank: " << popularityRank << std::endl;
    std::cout << "Available Tutors: " << tutorsAvailable << std::endl;
    
    if (isDeprecated) {
        std::cout << "Status: DEPRECATED" << std::endl;
    }
    
    std::cout << "\nDescription: " << description << std::endl;
    
    if (!documentationURL.empty()) {
        std::cout << "Documentation: " << documentationURL << std::endl;
    }
}

void AIModel::displayCapabilities() const {
    std::cout << "Capabilities:" << std::endl;
    for (const auto& capability : capabilities) {
        std::cout << "- " << capability << std::endl;
    }
    
    std::cout << "\nLimitations:" << std::endl;
    for (const auto& limitation : limitations) {
        std::cout << "- " << limitation << std::endl;
    }
    
    std::cout << "\nUse Cases:" << std::endl;
    for (const auto& useCase : useCases) {
        std::cout << "- " << useCase << std::endl;
    }
}

void AIModel::displayParameters() const {
    std::cout << "Parameters:" << std::endl;
    for (const auto& param : parameters) {
        std::cout << "- " << param.first << ": " << param.second << std::endl;
    }
}

// Operator overloading
std::ostream& operator<<(std::ostream& os, const AIModel& model) {
    os << "AI Model ID: " << model.modelId << std::endl;
    os << "Name: " << model.name << " (v" << model.version << ")" << std::endl;
    os << "Developer: " << model.developer << std::endl;
    os << "Category: " << model.category << std::endl;
    os << "Release Date: " << model.releaseDate << std::endl;
    os << "Complexity: " << model.getComplexityDescription() << " (" << model.complexityLevel << "/5)" << std::endl;
    os << "Status: " << (model.isDeprecated ? "DEPRECATED" : "Active") << std::endl;
    os << "Description: " << model.description << std::endl;
    
    return os;
}

std::istream& operator>>(std::istream& is, AIModel& model) {
    std::cout << "Enter Model ID: ";
    is >> model.modelId;
    is.ignore(); // Clear newline
    
    std::cout << "Enter Name: ";
    std::getline(is, model.name);
    
    std::cout << "Enter Version: ";
    std::getline(is, model.version);
    
    std::cout << "Enter Developer: ";
    std::getline(is, model.developer);
    
    std::cout << "Enter Category: ";
    std::getline(is, model.category);
    
    std::cout << "Enter Release Date (YYYY-MM-DD): ";
    std::getline(is, model.releaseDate);
    
    std::cout << "Enter Description: ";
    std::getline(is, model.description);
    
    std::cout << "Enter Complexity Level (1-5): ";
    is >> model.complexityLevel;
    is.ignore(); // Clear newline
    
    std::cout << "Enter Documentation URL: ";
    std::getline(is, model.documentationURL);
    
    std::string deprecated;
    std::cout << "Is Deprecated? (y/n): ";
    std::getline(is, deprecated);
    model.isDeprecated = (deprecated == "y" || deprecated == "Y");
    
    // For capabilities, limitations, use cases, and parameters,
    // we would typically implement another input method for adding these
    // one by one through the application interface
    
    return is;
}