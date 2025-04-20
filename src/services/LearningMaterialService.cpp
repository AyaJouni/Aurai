#include "include/services/LearningMaterialService.h"
#include "include/utils/Logger.h"
#include "include/utils/Exception.h"
#include <set>
#include <algorithm>
#include <iostream>

// Constructor
LearningMaterialService::LearningMaterialService() : nextMaterialId(1)
{
    loadMaterials();
}

// Destructor
LearningMaterialService::~LearningMaterialService()
{
    saveMaterials();
}

// Load materials from file/database
void LearningMaterialService::loadMaterials()
{
    // In a real implementation with database integration, this would load from db
    // For now, we'll create some sample materials

    auto material1 = std::make_shared<LearningMaterial>(
        1, "GPT-4 Architecture Overview",
        "A comprehensive overview of GPT-4's architecture, training process, and capabilities",
        "Document", "PDF", "Dr. Emily Johnson");
    material1->setCreationDate("2025-03-15");
    material1->setDifficultyLevel(3);
    material1->setEstimatedTimeMinutes(45);
    material1->setURL("https://resources.aitutoring.com/materials/gpt4-architecture.pdf");
    material1->updateRating(4.7);
    material1->setUsageCount(12);
    material1->addAIModel(1); // GPT-4
    material1->addTag("GPT-4");
    material1->addTag("Architecture");
    material1->addTag("Large Language Models");

    auto material2 = std::make_shared<LearningMaterial>(
        2, "Prompt Engineering Masterclass",
        "Learn advanced techniques for crafting effective prompts for large language models",
        "Video", "MP4", "Michael Lee");
    material2->setCreationDate("2025-02-28");
    material2->setDifficultyLevel(2);
    material2->setEstimatedTimeMinutes(120);
    material2->setURL("https://resources.aitutoring.com/materials/prompt-engineering-masterclass.mp4");
    material2->updateRating(4.9);
    material2->setUsageCount(25);
    material2->addAIModel(1); // GPT-4
    material2->addAIModel(3); // Claude
    material2->addTag("Prompt Engineering");
    material2->addTag("Best Practices");
    material2->addTag("Tutorials");

    auto material3 = std::make_shared<LearningMaterial>(
        3, "Image Generation Fundamentals",
        "An interactive notebook guiding you through the basics of AI image generation",
        "Interactive", "Notebook", "James Wilson");
    material3->setCreationDate("2025-04-01");
    material3->setDifficultyLevel(2);
    material3->setEstimatedTimeMinutes(90);
    material3->setLocalPath("materials/image-generation-fundamentals.ipynb");
    material3->updateRating(4.6);
    material3->setUsageCount(18);
    material3->addAIModel(2); // DALL-E 3
    material3->addTag("Image Generation");
    material3->addTag("Tutorial");
    material3->addTag("Notebook");

    auto material4 = std::make_shared<LearningMaterial>(
        4, "Advanced LLM Fine-tuning",
        "Detailed guide on fine-tuning large language models for specific applications",
        "Document", "PDF", "Dr. Emily Johnson");
    material4->setCreationDate("2025-03-25");
    material4->setDifficultyLevel(4);
    material4->setEstimatedTimeMinutes(60);
    material4->setURL("https://resources.aitutoring.com/materials/advanced-llm-finetuning.pdf");
    material4->updateRating(4.8);
    material4->setUsageCount(15);
    material4->addAIModel(1); // GPT-4
    material4->addAIModel(3); // Claude
    material4->addTag("Fine-tuning");
    material4->addTag("Advanced");
    material4->addTag("LLMs");

    // Add materials to collection
    materials.push_back(material1);
    materials.push_back(material2);
    materials.push_back(material3);
    materials.push_back(material4);

    nextMaterialId = 5; // Set next ID after creating sample materials

    Logger::getInstance().info("Loaded " + std::to_string(materials.size()) + " learning materials");
}

// Save materials to file/database
void LearningMaterialService::saveMaterials()
{
    // In a real implementation, this would save to database
    Logger::getInstance().info("Saved " + std::to_string(materials.size()) + " learning materials");
}

// Material management methods
bool LearningMaterialService::addMaterial(std::shared_ptr<LearningMaterial> material)
{
    // Set material ID if not already set
    if (material->getMaterialId() == 0)
    {
        material->setMaterialId(nextMaterialId++);
    }

    materials.push_back(material);
    saveMaterials();

    Logger::getInstance().info("Added new learning material: " + material->getTitle());
    return true;
}

bool LearningMaterialService::removeMaterial(int materialId)
{
    auto it = std::find_if(materials.begin(), materials.end(),
                           [materialId](const std::shared_ptr<LearningMaterial> &material)
                           {
                               return material->getMaterialId() == materialId;
                           });

    if (it != materials.end())
    {
        Logger::getInstance().info("Removed learning material: " + (*it)->getTitle());
        materials.erase(it);
        saveMaterials();
        return true;
    }

    return false;
}

bool LearningMaterialService::updateMaterial(int materialId, const std::string &title,
                                             const std::string &description, const std::string &type,
                                             const std::string &format, const std::string &author)
{
    auto material = getMaterialById(materialId);
    if (!material)
    {
        return false;
    }

    material->setTitle(title);
    material->setDescription(description);
    material->setType(type);
    material->setFormat(format);
    material->setAuthor(author);

    saveMaterials();
    Logger::getInstance().info("Updated learning material: " + material->getTitle());
    return true;
}

// Material retrieval methods
std::shared_ptr<LearningMaterial> LearningMaterialService::getMaterialById(int materialId) const
{
    for (const auto &material : materials)
    {
        if (material->getMaterialId() == materialId)
        {
            return material;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<LearningMaterial>> LearningMaterialService::getAllMaterials() const
{
    return materials;
}

std::vector<std::shared_ptr<LearningMaterial>> LearningMaterialService::getMaterialsByType(const std::string &type) const
{
    std::vector<std::shared_ptr<LearningMaterial>> results;

    for (const auto &material : materials)
    {
        if (material->getType() == type)
        {
            results.push_back(material);
        }
    }

    return results;
}

std::vector<std::shared_ptr<LearningMaterial>> LearningMaterialService::getMaterialsByFormat(const std::string &format) const
{
    std::vector<std::shared_ptr<LearningMaterial>> results;

    for (const auto &material : materials)
    {
        if (material->getFormat() == format)
        {
            results.push_back(material);
        }
    }

    return results;
}

std::vector<std::shared_ptr<LearningMaterial>> LearningMaterialService::getMaterialsByAuthor(const std::string &author) const
{
    std::vector<std::shared_ptr<LearningMaterial>> results;

    for (const auto &material : materials)
    {
        if (material->getAuthor() == author)
        {
            results.push_back(material);
        }
    }

    return results;
}

std::vector<std::shared_ptr<LearningMaterial>> LearningMaterialService::getMaterialsByDifficulty(int level) const
{
    std::vector<std::shared_ptr<LearningMaterial>> results;

    for (const auto &material : materials)
    {
        if (material->getDifficultyLevel() == level)
        {
            results.push_back(material);
        }
    }

    return results;
}

std::vector<std::shared_ptr<LearningMaterial>> LearningMaterialService::searchMaterialsByTitle(const std::string &title) const
{
    std::vector<std::shared_ptr<LearningMaterial>> results;

    std::string searchTitle = title;
    // Convert search title to lowercase for case-insensitive search
    std::transform(searchTitle.begin(), searchTitle.end(), searchTitle.begin(), ::tolower);

    for (const auto &material : materials)
    {
        std::string materialTitle = material->getTitle();
        std::transform(materialTitle.begin(), materialTitle.end(), materialTitle.begin(), ::tolower);

        if (materialTitle.find(searchTitle) != std::string::npos)
        {
            results.push_back(material);
        }
    }

    return results;
}

std::vector<std::shared_ptr<LearningMaterial>> LearningMaterialService::searchMaterialsByTag(const std::string &tag) const
{
    std::vector<std::shared_ptr<LearningMaterial>> results;

    for (const auto &material : materials)
    {
        if (material->hasTag(tag))
        {
            results.push_back(material);
        }
    }

    return results;
}

// Material content management
bool LearningMaterialService::addMaterialAIModel(int materialId, int aiModelId)
{
    auto material = getMaterialById(materialId);
    if (!material)
    {
        return false;
    }

    material->addAIModel(aiModelId);
    saveMaterials();
    return true;
}

bool LearningMaterialService::removeMaterialAIModel(int materialId, int aiModelId)
{
    auto material = getMaterialById(materialId);
    if (!material)
    {
        return false;
    }

    material->removeAIModel(aiModelId);
    saveMaterials();
    return true;
}

std::vector<std::shared_ptr<LearningMaterial>> LearningMaterialService::getMaterialsForAIModel(int aiModelId) const
{
    std::vector<std::shared_ptr<LearningMaterial>> results;

    for (const auto &material : materials)
    {
        if (material->isRelevantForModel(aiModelId))
        {
            results.push_back(material);
        }
    }

    return results;
}

// Tag management
bool LearningMaterialService::addMaterialTag(int materialId, const std::string &tag)
{
    auto material = getMaterialById(materialId);
    if (!material)
    {
        return false;
    }

    material->addTag(tag);
    saveMaterials();
    return true;
}

bool LearningMaterialService::removeMaterialTag(int materialId, const std::string &tag)
{
    auto material = getMaterialById(materialId);
    if (!material)
    {
        return false;
    }

    material->removeTag(tag);
    saveMaterials();
    return true;
}

std::vector<std::string> LearningMaterialService::getAllTags() const
{
    std::vector<std::string> allTags;
    std::set<std::string> uniqueTags;

    for (const auto &material : materials)
    {
        const auto &tags = material->getTags();
        uniqueTags.insert(tags.begin(), tags.end());
    }

    allTags.assign(uniqueTags.begin(), uniqueTags.end());
    return allTags;
}

// Material attributes management
bool LearningMaterialService::updateMaterialDifficulty(int materialId, int level)
{
    auto material = getMaterialById(materialId);
    if (!material)
    {
        return false;
    }

    material->setDifficultyLevel(level);
    saveMaterials();
    return true;
}

bool LearningMaterialService::updateMaterialLocation(int materialId, const std::string &url, const std::string &localPath)
{
    auto material = getMaterialById(materialId);
    if (!material)
    {
        return false;
    }

    material->setURL(url);
    material->setLocalPath(localPath);
    saveMaterials();
    return true;
}

bool LearningMaterialService::updateMaterialTime(int materialId, int estimatedMinutes)
{
    auto material = getMaterialById(materialId);
    if (!material)
    {
        return false;
    }

    material->setEstimatedTimeMinutes(estimatedMinutes);
    saveMaterials();
    return true;
}

// Usage and rating
bool LearningMaterialService::updateMaterialRating(int materialId, double rating)
{
    auto material = getMaterialById(materialId);
    if (!material)
    {
        return false;
    }

    material->updateRating(rating);
    saveMaterials();
    return true;
}

bool LearningMaterialService::incrementMaterialUsage(int materialId)
{
    auto material = getMaterialById(materialId);
    if (!material)
    {
        return false;
    }

    material->incrementUsageCount();
    saveMaterials();
    return true;
}

double LearningMaterialService::getMaterialRating(int materialId) const
{
    auto material = getMaterialById(materialId);
    if (!material)
    {
        return 0.0;
    }

    return material->getRating();
}

int LearningMaterialService::getMaterialUsageCount(int materialId) const
{
    auto material = getMaterialById(materialId);
    if (!material)
    {
        return 0;
    }

    return material->getUsageCount();
}

// Analytics methods
std::vector<std::shared_ptr<LearningMaterial>> LearningMaterialService::getMostUsedMaterials(int count) const
{
    auto sortedMaterials = materials;

    std::sort(sortedMaterials.begin(), sortedMaterials.end(),
              [](const std::shared_ptr<LearningMaterial> &a, const std::shared_ptr<LearningMaterial> &b)
              {
                  return a->getUsageCount() > b->getUsageCount();
              });

    int resultCount = std::min(static_cast<int>(sortedMaterials.size()), count);
    return std::vector<std::shared_ptr<LearningMaterial>>(sortedMaterials.begin(), sortedMaterials.begin() + resultCount);
}

// Analytics methods (continued)
std::vector<std::shared_ptr<LearningMaterial>> LearningMaterialService::getTopRatedMaterials(int count) const
{
    auto sortedMaterials = materials;

    std::sort(sortedMaterials.begin(), sortedMaterials.end(),
              [](const std::shared_ptr<LearningMaterial> &a, const std::shared_ptr<LearningMaterial> &b)
              {
                  return a->getRating() > b->getRating();
              });

    int resultCount = std::min(static_cast<int>(sortedMaterials.size()), count);
    return std::vector<std::shared_ptr<LearningMaterial>>(sortedMaterials.begin(), sortedMaterials.begin() + resultCount);
}

std::map<std::string, int> LearningMaterialService::getMaterialTypeDistribution() const
{
    std::map<std::string, int> typeDistribution;

    for (const auto &material : materials)
    {
        typeDistribution[material->getType()]++;
    }

    return typeDistribution;
}

// Recommendations
std::vector<std::shared_ptr<LearningMaterial>> LearningMaterialService::getRecommendedMaterials(int clientId) const
{
    // In a real implementation, this would use client's learning history, proficiency levels, etc.
    // For now, just return top rated materials
    return getTopRatedMaterials(5);
}

std::vector<std::shared_ptr<LearningMaterial>> LearningMaterialService::getRelatedMaterials(int materialId) const
{
    auto material = getMaterialById(materialId);
    if (!material)
    {
        return {};
    }

    std::vector<std::shared_ptr<LearningMaterial>> related;
    std::set<int> materialIds;

    // Get materials with matching tags
    const auto &tags = material->getTags();
    for (const auto &tag : tags)
    {
        auto taggedMaterials = searchMaterialsByTag(tag);
        for (const auto &taggedMaterial : taggedMaterials)
        {
            if (taggedMaterial->getMaterialId() != materialId)
            {
                materialIds.insert(taggedMaterial->getMaterialId());
            }
        }
    }

    // Get materials for the same AI models
    const auto &aiModelIds = material->getAIModelIds();
    for (int aiModelId : aiModelIds)
    {
        auto modelMaterials = getMaterialsForAIModel(aiModelId);
        for (const auto &modelMaterial : modelMaterials)
        {
            if (modelMaterial->getMaterialId() != materialId)
            {
                materialIds.insert(modelMaterial->getMaterialId());
            }
        }
    }

    // Convert set of IDs to material objects
    for (int id : materialIds)
    {
        related.push_back(getMaterialById(id));
    }

    // Sort by rating
    std::sort(related.begin(), related.end(),
              [](const std::shared_ptr<LearningMaterial> &a, const std::shared_ptr<LearningMaterial> &b)
              {
                  return a->getRating() > b->getRating();
              });

    return related;
}

std::vector<std::shared_ptr<LearningMaterial>> LearningMaterialService::getLearningPathMaterials(int aiModelId, int clientProficiency) const
{
    auto modelMaterials = getMaterialsForAIModel(aiModelId);

    // Filter materials by difficulty level based on client proficiency
    std::vector<std::shared_ptr<LearningMaterial>> pathMaterials;
    for (const auto &material : modelMaterials)
    {
        // Include materials with difficulty level around client's proficiency level
        if (abs(material->getDifficultyLevel() - clientProficiency) <= 1)
        {
            pathMaterials.push_back(material);
        }
    }

    // Sort by difficulty level (ascending)
    std::sort(pathMaterials.begin(), pathMaterials.end(),
              [](const std::shared_ptr<LearningMaterial> &a, const std::shared_ptr<LearningMaterial> &b)
              {
                  return a->getDifficultyLevel() < b->getDifficultyLevel();
              });

    return pathMaterials;
}