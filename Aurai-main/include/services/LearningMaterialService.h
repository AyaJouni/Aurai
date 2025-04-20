// LearningMaterialService.h
#ifndef LEARNING_MATERIAL_SERVICE_H
#define LEARNING_MATERIAL_SERVICE_H

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "../models/LearningMaterial.h"

class LearningMaterialService {
private:
    std::vector<std::shared_ptr<LearningMaterial>> materials;
    int nextMaterialId;
    
    // Private helper methods
    void loadMaterials();  // Load materials from file
    void saveMaterials();  // Save materials to file
    
public:
    // Constructor and Destructor
    LearningMaterialService();
    ~LearningMaterialService();
    
    // Material management methods
    bool addMaterial(std::shared_ptr<LearningMaterial> material);
    bool removeMaterial(int materialId);
    bool updateMaterial(int materialId, const std::string& title, 
                      const std::string& description, const std::string& type,
                      const std::string& format, const std::string& author);
    
    // Material retrieval methods
    std::shared_ptr<LearningMaterial> getMaterialById(int materialId) const;
    std::vector<std::shared_ptr<LearningMaterial>> getAllMaterials() const;
    std::vector<std::shared_ptr<LearningMaterial>> getMaterialsByType(const std::string& type) const;
    std::vector<std::shared_ptr<LearningMaterial>> getMaterialsByFormat(const std::string& format) const;
    std::vector<std::shared_ptr<LearningMaterial>> getMaterialsByAuthor(const std::string& author) const;
    std::vector<std::shared_ptr<LearningMaterial>> getMaterialsByDifficulty(int level) const;
    std::vector<std::shared_ptr<LearningMaterial>> searchMaterialsByTitle(const std::string& title) const;
    std::vector<std::shared_ptr<LearningMaterial>> searchMaterialsByTag(const std::string& tag) const;
    
    // Material content management
    bool addMaterialAIModel(int materialId, int aiModelId);
    bool removeMaterialAIModel(int materialId, int aiModelId);
    std::vector<std::shared_ptr<LearningMaterial>> getMaterialsForAIModel(int aiModelId) const;
    
    // Tag management
    bool addMaterialTag(int materialId, const std::string& tag);
    bool removeMaterialTag(int materialId, const std::string& tag);
    std::vector<std::string> getAllTags() const;
    
    // Material attributes management
    bool updateMaterialDifficulty(int materialId, int level);
    bool updateMaterialLocation(int materialId, const std::string& url, const std::string& localPath);
    bool updateMaterialTime(int materialId, int estimatedMinutes);
    
    // Usage and rating
    bool updateMaterialRating(int materialId, double rating);
    bool incrementMaterialUsage(int materialId);
    double getMaterialRating(int materialId) const;
    int getMaterialUsageCount(int materialId) const;
    
    // Analytics methods
    std::vector<std::shared_ptr<LearningMaterial>> getMostUsedMaterials(int count) const;
    std::vector<std::shared_ptr<LearningMaterial>> getTopRatedMaterials(int count) const;
    std::map<std::string, int> getMaterialTypeDistribution() const;
    
    // Recommendations
    std::vector<std::shared_ptr<LearningMaterial>> getRecommendedMaterials(int clientId) const;
    std::vector<std::shared_ptr<LearningMaterial>> getRelatedMaterials(int materialId) const;
    std::vector<std::shared_ptr<LearningMaterial>> getLearningPathMaterials(int aiModelId, int clientProficiency) const;
};

#endif // LEARNING_MATERIAL_SERVICE_H