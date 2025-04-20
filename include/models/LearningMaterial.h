// LearningMaterial.h
#ifndef LEARNING_MATERIAL_H
#define LEARNING_MATERIAL_H

#include <string>
#include <vector>
#include <iostream>

class LearningMaterial {
private:
    int materialId;
    std::string title;
    std::string description;
    std::string type;              // "Document", "Video", "Interactive", "Exercise", etc.
    std::string format;            // "PDF", "MP4", "Notebook", etc.
    std::string author;
    std::string creationDate;
    std::vector<int> aiModelIds;   // Associated AI models
    std::vector<std::string> tags; // Keywords/tags for searching
    int difficultyLevel;           // 1-5 scale (1:Beginner, 5:Advanced)
    std::string url;               // Link to the material if external
    std::string localPath;         // Path to file if stored locally
    int estimatedTimeMinutes;      // Estimated time to complete
    double rating;                 // Average user rating
    int usageCount;                // How many times used in sessions
    
public:
    // Constructors
    LearningMaterial();
    LearningMaterial(int materialId, const std::string& title, 
                     const std::string& description, const std::string& type,
                     const std::string& format, const std::string& author);
    
    // Getters and setters
    int getMaterialId() const;
    void setMaterialId(int id);
    
    std::string getTitle() const;
    void setTitle(const std::string& title);
    
    std::string getDescription() const;
    void setDescription(const std::string& description);
    
    std::string getType() const;
    void setType(const std::string& type);
    
    std::string getFormat() const;
    void setFormat(const std::string& format);
    
    std::string getAuthor() const;
    void setAuthor(const std::string& author);
    
    std::string getCreationDate() const;
    void setCreationDate(const std::string& date);
    
    const std::vector<int>& getAIModelIds() const;
    void addAIModel(int modelId);
    void removeAIModel(int modelId);
    bool isRelevantForModel(int modelId) const;
    
    const std::vector<std::string>& getTags() const;
    void addTag(const std::string& tag);
    void removeTag(const std::string& tag);
    bool hasTag(const std::string& tag) const;
    
    int getDifficultyLevel() const;
    void setDifficultyLevel(int level);
    
    std::string getURL() const;
    void setURL(const std::string& url);
    
    std::string getLocalPath() const;
    void setLocalPath(const std::string& path);
    
    int getEstimatedTimeMinutes() const;
    void setEstimatedTimeMinutes(int minutes);
    
    double getRating() const;
    void updateRating(double newRating);
    
    int getUsageCount() const;
    void incrementUsageCount();
    void setUsageCount(int count);
    
    // Utility methods
    std::string getDifficultyDescription() const;  // Returns text description of difficulty
    std::string getFormattedEstimatedTime() const; // Returns "HH:MM" format
    bool isDigital() const;  // Returns whether the material is in digital format
    
    // Display material info
    void displayInfo() const;
    void displayTags() const;
    
    // Operator overloading
    friend std::ostream& operator<<(std::ostream& os, const LearningMaterial& material);
    friend std::istream& operator>>(std::istream& is, LearningMaterial& material);
};

#endif // LEARNING_MATERIAL_H