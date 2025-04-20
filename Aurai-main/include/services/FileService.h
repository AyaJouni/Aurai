// FileService.h
#ifndef FILE_SERVICE_H
#define FILE_SERVICE_H

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>

// Generic template class for serialization and deserialization of data
template <typename T>
class FileService {
private:
    std::string filename;
    
    // Helper methods for serialization
    virtual std::string serializeObject(const T& object) const = 0;
    virtual T deserializeObject(const std::string& data) const = 0;
    
public:
    // Constructor
    FileService(const std::string& filename) : filename(filename) {}
    
    // Virtual destructor
    virtual ~FileService() = default;
    
    // File operations
    bool saveToFile(const std::vector<T>& objects) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file for writing: " << filename << std::endl;
            return false;
        }
        
        for (const auto& object : objects) {
            file << serializeObject(object) << std::endl;
        }
        
        file.close();
        return true;
    }
    
    std::vector<T> loadFromFile() const {
        std::vector<T> objects;
        std::ifstream file(filename);
        
        if (!file.is_open()) {
            std::cerr << "Warning: Could not open file for reading: " << filename << std::endl;
            return objects;
        }
        
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                objects.push_back(deserializeObject(line));
            }
        }
        
        file.close();
        return objects;
    }
    
    bool appendToFile(const T& object) const {
        std::ofstream file(filename, std::ios::app);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file for appending: " << filename << std::endl;
            return false;
        }
        
        file << serializeObject(object) << std::endl;
        file.close();
        return true;
    }
    
    bool fileExists() const {
        std::ifstream file(filename);
        return file.good();
    }
    
    bool createEmptyFile() const {
        if (fileExists()) {
            return true;
        }
        
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not create file: " << filename << std::endl;
            return false;
        }
        
        file.close();
        return true;
    }
    
    bool clearFile() const {
        std::ofstream file(filename, std::ios::trunc);
        if (!file.is_open()) {
            std::cerr << "Error: Could not clear file: " << filename << std::endl;
            return false;
        }
        
        file.close();
        return true;
    }
    
    std::string getFilename() const {
        return filename;
    }
    
    void setFilename(const std::string& newFilename) {
        filename = newFilename;
    }
};

// Example of specific implementation for a model type (would be in .cpp file)
/*
class ClientFileService : public FileService<Client> {
private:
    std::string serializeObject(const Client& client) const override {
        // Implementation of how to convert a Client to a string
        std::stringstream ss;
        ss << client.getClientId() << "|"
           << client.getFirstName() << "|"
           << client.getLastName() << "|"
           << client.getEmail() << "|"
           << // ... other fields
        return ss.str();
    }
    
    Client deserializeObject(const std::string& data) const override {
        // Implementation of how to convert a string back to a Client
        std::stringstream ss(data);
        std::string token;
        std::vector<std::string> tokens;
        
        while (std::getline(ss, token, '|')) {
            tokens.push_back(token);
        }
        
        // Validate we have enough tokens
        if (tokens.size() < 4) {
            throw std::runtime_error("Invalid client data format");
        }
        
        Client client;
        client.setClientId(std::stoi(tokens[0]));
        client.setFirstName(tokens[1]);
        client.setLastName(tokens[2]);
        client.setEmail(tokens[3]);
        // ... set other fields
        
        return client;
    }
    
public:
    ClientFileService(const std::string& filename = "data/clients.dat")
        : FileService<Client>(filename) {}
};
*/

#endif // FILE_SERVICE_H