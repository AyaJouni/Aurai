#include "include/services/AIModelService.h"
#include "include/utils/Logger.h"
#include "include/utils/Exception.h"
#include <algorithm>
#include <iostream>

// Constructor
AIModelService::AIModelService() : nextModelId(1) {
    loadAIModels();
}

// Destructor
AIModelService::~AIModelService() {
    saveAIModels();
}

// Load AI models from file (stub implementation)
void AIModelService::loadAIModels() {
    // In a real implementation, this would load from a file
    // For now, we'll create some sample AI models for testing
    
    // GPT-4
    auto gpt4 = std::make_shared<AIModel>(
        1, "GPT-4", "4.0", 
        "OpenAI", "Large Language Model",
        "2023-03-14", "Advanced language model capable of understanding and generating human-like text",
        4 // Complexity level
    );
    
    gpt4->addCapability("Natural language understanding");
    gpt4->addCapability("Text generation");
    gpt4->addCapability("Translation");
    gpt4->addCapability("Code generation");
    
    gpt4->addLimitation("May generate incorrect information");
    gpt4->addLimitation("Limited knowledge cutoff");
    
    gpt4->addUseCase("Content creation");
    gpt4->addUseCase("Customer support automation");
    gpt4->addUseCase("Programming assistance");
    
    gpt4->addParameter("Temperature", "Controls randomness of outputs");
    gpt4->addParameter("Max tokens", "Controls length of generated text");
    
    gpt4->setPopularityRank(1);
    gpt4->setTutorsAvailable(4);
    gpt4->setDocumentationURL("https://platform.openai.com/docs/models/gpt-4");
    
    // DALL-E 3
    auto dalle3 = std::make_shared<AIModel>(
        2, "DALL-E 3", "3.0", 
        "OpenAI", "Image Generation",
        "2023-10-03", "Image generation model that can create detailed images from text descriptions",
        3 // Complexity level
    );
    
    dalle3->addCapability("Image generation from text");
    dalle3->addCapability("Style adaptation");
    dalle3->addCapability("Artistic rendering");
    
    dalle3->addLimitation("May misinterpret complex prompts");
    dalle3->addLimitation("Limited understanding of physical constraints");
    
    dalle3->addUseCase("Marketing materials");
    dalle3->addUseCase("Concept art");
    dalle3->addUseCase("Visual storytelling");
    
    dalle3->addParameter("Style", "Controls artistic style of generated images");
    dalle3->addParameter("Size", "Controls dimensions of output images");
    
    dalle3->setPopularityRank(2);
    dalle3->setTutorsAvailable(3);
    dalle3->setDocumentationURL("https://platform.openai.com/docs/models/dall-e-3");
    
    // Claude
    auto claude = std::make_shared<AIModel>(
        3, "Claude", "2.0", 
        "Anthropic", "Large Language Model",
        "2023-07-11", "Conversational AI assistant focused on helpful, harmless, and honest interactions",
        3 // Complexity level
    );
    
    claude->addCapability("Natural language understanding");
    claude->addCapability("Contextual responses");
    claude->addCapability("Long context window");
    
    claude->addLimitation("May refuse certain types of content");
    claude->addLimitation("Cannot browse the internet");
    
    claude->addUseCase("Customer support");
    claude->addUseCase("Content creation");
    claude->addUseCase("Research assistance");
    
    claude->addParameter("Temperature", "Controls randomness of outputs");
    claude->addParameter("Max tokens", "Controls length of generated text");
    
    claude->setPopularityRank(3);
    claude->setTutorsAvailable(2);
    claude->setDocumentationURL("https://www.anthropic.com/claude");
    
    // Add models to collection
    aiModels.push_back(gpt4);
    aiModels.push_back(dalle3);
    aiModels.push_back(claude);
    
    nextModelId = 4; // Set next ID after creating sample models
    
    Logger::getInstance().info("Loaded " + std::to_string(aiModels.size()) + " AI models");
}

// Save AI models to file (stub implementation)
void AIModelService::saveAIModels() {
    // In a real implementation, this would save to a file
    Logger::getInstance().info("Saved " + std::to_string(aiModels.size()) + " AI models");
}

// Model management methods
bool AIModelService::addAIModel(std::shared_ptr<AIModel> model) {
    // Set model ID if not already set
    if (model->getModelId() == 0) {
        model->setModelId(nextModelId++);
    }
    
    aiModels.push_back(model);
    saveAIModels();
    
    Logger::getInstance().info("Added new AI model: " + model->getName());
    return true;
}

bool AIModelService::removeAIModel(int modelId) {
    auto it = std::find_if(aiModels.begin(), aiModels.end(), 
        [modelId](const std::shared_ptr<AIModel>& model) {
            return model->getModelId() == modelId;
        });
    
    if (it != aiModels.end()) {
        Logger::getInstance().info("Removed AI model: " + (*it)->getName());
        aiModels.erase(it);
        saveAIModels();
        return true;
    }
    
    return false;
}

bool AIModelService::updateAIModel(int modelId, const std::string& name, 
                                 const std::string& version, const std::string& developer,
                                 const std::string& category, const std::string& description) {
    auto model = getModelById(modelId);
    if (!model) {
        return false;
    }
    
    model->setName(name);
    model->setVersion(version);
    model->setDeveloper(developer);
    model->setCategory(category);
    model->setDescription(description);
    
    saveAIModels();
    Logger::getInstance().info("Updated AI model: " + model->getName());
    return true;
}

// Model retrieval methods
std::shared_ptr<AIModel> AIModelService::getModelById(int modelId) const {
    for (const auto& model : aiModels) {
        if (model->getModelId() == modelId) {
            return model;
        }
    }
    return nullptr;
}

std::shared_ptr<AIModel> AIModelService::getModelByName(const std::string& name) const {
    for (const auto& model : aiModels) {
        if (model->getName() == name) {
            return model;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<AIModel>> AIModelService::getAllModels() const {
    return aiModels;
}

std::vector<std::shared_ptr<AIModel>> AIModelService::getModelsByCategory(const std::string& category) const {
    std::vector<std::shared_ptr<AIModel>> results;
    
    for (const auto& model : aiModels) {
        if (model->getCategory() == category) {
            results.push_back(model);
        }
    }
    
    return results;
}

std::vector<std::shared_ptr<AIModel>> AIModelService::getModelsByDeveloper(const std::string& developer) const {
    std::vector<std::shared_ptr<AIModel>> results;
    
    for (const auto& model : aiModels) {
        if (model->getDeveloper() == developer) {
            results.push_back(model);
        }
    }
    
    return results;
}

std::vector<std::shared_ptr<AIModel>> AIModelService::getModelsByComplexity(int complexityLevel) const {
    std::vector<std::shared_ptr<AIModel>> results;
    
    for (const auto& model : aiModels) {
        if (model->getComplexityLevel() == complexityLevel) {
            results.push_back(model);
        }
    }
    
    return results;
}

// Model attributes management
bool AIModelService::addModelCapability(int modelId, const std::string& capability) {
    auto model = getModelById(modelId);
    if (!model) {
        return false;
    }
    
    model->addCapability(capability);
    saveAIModels();
    return true;
}

bool AIModelService::removeModelCapability(int modelId, const std::string& capability) {
    auto model = getModelById(modelId);
    if (!model) {
        return false;
    }
    
    model->removeCapability(capability);
    saveAIModels();
    return true;
}

bool AIModelService::addModelLimitation(int modelId, const std::string& limitation) {
    auto model = getModelById(modelId);
    if (!model) {
        return false;
    }
    
    model->addLimitation(limitation);
    saveAIModels();
    return true;
}

bool AIModelService::removeModelLimitation(int modelId, const std::string& limitation) {
    auto model = getModelById(modelId);
    if (!model) {
        return false;
    }
    
    model->removeLimitation(limitation);
    saveAIModels();
    return true;
}

bool AIModelService::addModelUseCase(int modelId, const std::string& useCase) {
    auto model = getModelById(modelId);
    if (!model) {
        return false;
    }
    
    model->addUseCase(useCase);
    saveAIModels();
    return true;
}

bool AIModelService::removeModelUseCase(int modelId, const std::string& useCase) {
    auto model = getModelById(modelId);
    if (!model) {
        return false;
    }
    
    model->removeUseCase(useCase);
    saveAIModels();
    return true;
}

bool AIModelService::addModelParameter(int modelId, const std::string& param, const std::string& description) {
    auto model = getModelById(modelId);
    if (!model) {
        return false;
    }
    
    model->addParameter(param, description);
    saveAIModels();
    return true;
}

bool AIModelService::removeModelParameter(int modelId, const std::string& param) {
    auto model = getModelById(modelId);
    if (!model) {
        return false;
    }
    
    model->removeParameter(param);
    saveAIModels();
    return true;
}

// Model status management
bool AIModelService::updateModelComplexity(int modelId, int level) {
    auto model = getModelById(modelId);
    if (!model) {
        return false;
    }
    
    model->setComplexityLevel(level);
    saveAIModels();
    return true;
}

bool AIModelService::updateModelPopularity(int modelId, int rank) {
    auto model = getModelById(modelId);
    if (!model) {
        return false;
    }
    
    model->setPopularityRank(rank);
    saveAIModels();
    return true;
}

bool AIModelService::updateTutorsAvailable(int modelId, int count) {
    auto model = getModelById(modelId);
    if (!model) {
        return false;
    }
    
    model->setTutorsAvailable(count);
    saveAIModels();
    return true;
}

bool AIModelService::markModelAsDeprecated(int modelId, bool deprecated) {
    auto model = getModelById(modelId);
    if (!model) {
        return false;
    }
    
    model->setIsDeprecated(deprecated);
    saveAIModels();
    return true;
}

// Documentation management
bool AIModelService::updateModelDocumentation(int modelId, const std::string& url) {
    auto model = getModelById(modelId);
    if (!model) {
        return false;
    }
    
    model->setDocumentationURL(url);
    saveAIModels();
    return true;
}

std::string AIModelService::getModelDocumentation(int modelId) const {
    auto model = getModelById(modelId);
    if (!model) {
        return "";
    }
    
    return model->getDocumentationURL();
}

// Analytics methods
std::vector<std::shared_ptr<AIModel>> AIModelService::getMostPopularModels(int count) const {
    // Create a copy of the models
    auto sortedModels = aiModels;
    
    // Sort by popularity rank (ascending)
    std::sort(sortedModels.begin(), sortedModels.end(),
              [](const std::shared_ptr<AIModel>& a, const std::shared_ptr<AIModel>& b) {
                  return a->getPopularityRank() < b->getPopularityRank();
              });
    
    // Return the requested number (or all if count is larger)
    int resultCount = std::min(static_cast<int>(sortedModels.size()), count);
    return std::vector<std::shared_ptr<AIModel>>(sortedModels.begin(), sortedModels.begin() + resultCount);
}

std::map<std::string, int> AIModelService::getModelCategoryCounts() const {
    std::map<std::string, int> categoryCounts;
    
    for (const auto& model : aiModels) {
        categoryCounts[model->getCategory()]++;
    }
    
    return categoryCounts;
}

std::map<std::string, int> AIModelService::getDeveloperModelCounts() const {
    std::map<std::string, int> developerCounts;
    
    for (const auto& model : aiModels) {
        developerCounts[model->getDeveloper()]++;
    }
    
    return developerCounts;
}

double AIModelService::getAverageModelComplexity() const {
    if (aiModels.empty()) {
        return 0.0;
    }
    
    double totalComplexity = 0.0;
    for (const auto& model : aiModels) {
        totalComplexity += model->getComplexityLevel();
    }
    
    return totalComplexity / aiModels.size();
}

// Learning path recommendations (stub implementations)
std::vector<std::shared_ptr<AIModel>> AIModelService::getRecommendedLearningPath(int clientId) const {
    // This would normally use client's profile and progress to recommend models
    // For now, just return models sorted by complexity
    auto sortedModels = aiModels;
    
    std::sort(sortedModels.begin(), sortedModels.end(),
              [](const std::shared_ptr<AIModel>& a, const std::shared_ptr<AIModel>& b) {
                  return a->getComplexityLevel() < b->getComplexityLevel();
              });
    
    return sortedModels;
}

std::vector<std::shared_ptr<AIModel>> AIModelService::getRelatedModels(int modelId) const {
    auto model = getModelById(modelId);
    if (!model) {
        return {};
    }
    
    // For now, just return models in the same category
    return getModelsByCategory(model->getCategory());
}

std::vector<std::shared_ptr<AIModel>> AIModelService::getPrerequisiteModels(int modelId) const {
    auto model = getModelById(modelId);
    if (!model) {
        return {};
    }
    
    // For now, return models of the same category with lower complexity
    std::vector<std::shared_ptr<AIModel>> prerequisites;
    
    for (const auto& other : aiModels) {
        if (other->getCategory() == model->getCategory() && 
            other->getComplexityLevel() < model->getComplexityLevel()) {
            prerequisites.push_back(other);
        }
    }
    
    return prerequisites;
}

std::vector<std::shared_ptr<AIModel>> AIModelService::getNextLevelModels(int modelId) const {
    auto model = getModelById(modelId);
    if (!model) {
        return {};
    }
    
    // For now, return models of the same category with higher complexity
    std::vector<std::shared_ptr<AIModel>> nextLevelModels;
    
    for (const auto& other : aiModels) {
        if (other->getCategory() == model->getCategory() && 
            other->getComplexityLevel() > model->getComplexityLevel()) {
            nextLevelModels.push_back(other);
        }
    }
    
    return nextLevelModels;
}