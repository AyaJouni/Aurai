// AIModelService.h
#ifndef AI_MODEL_SERVICE_H
#define AI_MODEL_SERVICE_H

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "../models/AIModel.h"

class AIModelService {
private:
    std::vector<std::shared_ptr<AIModel>> aiModels;
    int nextModelId;
    
    // Private helper methods
    void loadAIModels();  // Load AI models from file
    void saveAIModels();  // Save AI models to file
    
public:
    // Constructor and Destructor
    AIModelService();
    ~AIModelService();
    
    // Model management methods
    bool addAIModel(std::shared_ptr<AIModel> model);
    bool removeAIModel(int modelId);
    bool updateAIModel(int modelId, const std::string& name, 
                     const std::string& version, const std::string& developer,
                     const std::string& category, const std::string& description);
    
    // Model retrieval methods
    std::shared_ptr<AIModel> getModelById(int modelId) const;
    std::shared_ptr<AIModel> getModelByName(const std::string& name) const;
    std::vector<std::shared_ptr<AIModel>> getAllModels() const;
    std::vector<std::shared_ptr<AIModel>> getModelsByCategory(const std::string& category) const;
    std::vector<std::shared_ptr<AIModel>> getModelsByDeveloper(const std::string& developer) const;
    std::vector<std::shared_ptr<AIModel>> getModelsByComplexity(int complexityLevel) const;
    
    // Model attributes management
    bool addModelCapability(int modelId, const std::string& capability);
    bool removeModelCapability(int modelId, const std::string& capability);
    bool addModelLimitation(int modelId, const std::string& limitation);
    bool removeModelLimitation(int modelId, const std::string& limitation);
    bool addModelUseCase(int modelId, const std::string& useCase);
    bool removeModelUseCase(int modelId, const std::string& useCase);
    bool addModelParameter(int modelId, const std::string& param, const std::string& description);
    bool removeModelParameter(int modelId, const std::string& param);
    
    // Model status management
    bool updateModelComplexity(int modelId, int level);
    bool updateModelPopularity(int modelId, int rank);
    bool updateTutorsAvailable(int modelId, int count);
    bool markModelAsDeprecated(int modelId, bool deprecated = true);
    
    // Documentation management
    bool updateModelDocumentation(int modelId, const std::string& url);
    std::string getModelDocumentation(int modelId) const;
    
    // Analytics methods
    std::vector<std::shared_ptr<AIModel>> getMostPopularModels(int count) const;
    std::map<std::string, int> getModelCategoryCounts() const;
    std::map<std::string, int> getDeveloperModelCounts() const;
    double getAverageModelComplexity() const;
    
    // Learning path recommendations
    std::vector<std::shared_ptr<AIModel>> getRecommendedLearningPath(int clientId) const;
    std::vector<std::shared_ptr<AIModel>> getRelatedModels(int modelId) const;
    std::vector<std::shared_ptr<AIModel>> getPrerequisiteModels(int modelId) const;
    std::vector<std::shared_ptr<AIModel>> getNextLevelModels(int modelId) const;
};

#endif // AI_MODEL_SERVICE_H