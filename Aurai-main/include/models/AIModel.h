// AIModel.h
#ifndef AI_MODEL_H
#define AI_MODEL_H

#include <string>
#include <vector>
#include <map>
#include <iostream>

class AIModel {
private:
    int modelId;
    std::string name;
    std::string version;
    std::string developer;
    std::string category;                      // "LLM", "Computer Vision", "Generative AI", etc.
    std::string releaseDate;
    std::string description;
    std::vector<std::string> capabilities;
    std::vector<std::string> limitations;
    std::vector<std::string> useCases;
    std::map<std::string, std::string> parameters;  // Key parameters and their descriptions
    int complexityLevel;                        // 1-5 scale
    int popularityRank;                         // Based on client interest
    int tutorsAvailable;                        // Number of tutors who can teach this
    std::string documentationURL;
    bool isDeprecated;
    
public:
    // Constructors
    AIModel();
    AIModel(int modelId, const std::string& name, const std::string& version,
            const std::string& developer, const std::string& category,
            const std::string& releaseDate, const std::string& description,
            int complexityLevel);
    
    // Getters and setters
    int getModelId() const;
    void setModelId(int id);
    
    std::string getName() const;
    void setName(const std::string& name);
    
    std::string getVersion() const;
    void setVersion(const std::string& version);
    
    std::string getDeveloper() const;
    void setDeveloper(const std::string& developer);
    
    std::string getCategory() const;
    void setCategory(const std::string& category);
    
    std::string getReleaseDate() const;
    void setReleaseDate(const std::string& date);
    
    std::string getDescription() const;
    void setDescription(const std::string& description);
    
    const std::vector<std::string>& getCapabilities() const;
    void addCapability(const std::string& capability);
    void removeCapability(const std::string& capability);
    
    const std::vector<std::string>& getLimitations() const;
    void addLimitation(const std::string& limitation);
    void removeLimitation(const std::string& limitation);
    
    const std::vector<std::string>& getUseCases() const;
    void addUseCase(const std::string& useCase);
    void removeUseCase(const std::string& useCase);
    
    const std::map<std::string, std::string>& getParameters() const;
    void addParameter(const std::string& param, const std::string& description);
    void removeParameter(const std::string& param);
    std::string getParameterDescription(const std::string& param) const;
    
    int getComplexityLevel() const;
    void setComplexityLevel(int level);
    
    int getPopularityRank() const;
    void setPopularityRank(int rank);
    
    int getTutorsAvailable() const;
    void setTutorsAvailable(int count);
    void incrementTutorsAvailable();
    void decrementTutorsAvailable();
    
    std::string getDocumentationURL() const;
    void setDocumentationURL(const std::string& url);
    
    bool getIsDeprecated() const;
    void setIsDeprecated(bool deprecated);
    
    // Utility methods
    std::string getComplexityDescription() const;  // Returns text description of complexity
    bool hasCapability(const std::string& capability) const;
    bool isCompatibleWith(const std::string& otherModelName) const;
    
    // Display model info
    void displayInfo() const;
    void displayCapabilities() const;
    void displayParameters() const;
    
    // Operator overloading
    friend std::ostream& operator<<(std::ostream& os, const AIModel& model);
    friend std::istream& operator>>(std::istream& is, AIModel& model);
};

#endif // AI_MODEL_H