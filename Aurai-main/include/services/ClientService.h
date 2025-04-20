#ifndef CLIENT_SERVICE_H
#define CLIENT_SERVICE_H

#include <memory>
#include <vector>
#include <map>
#include <string>
#include "../models/Client.h"

class ClientService
{
private:
    std::vector<std::shared_ptr<Client>> clients;
    int nextClientId;

    // Private helper methods
    void loadClients();
    void saveClients();
    bool isValidEmail(const std::string &email) const;
    bool isValidPhone(const std::string &phone) const;

public:
    ClientService();
    ~ClientService();

    // Client management methods
    bool addClient(std::shared_ptr<Client> client);
    bool removeClient(int clientId);
    bool updateClientDetails(int clientId,
                             const std::string &firstName,
                             const std::string &lastName,
                             const std::string &email,
                             const std::string &phone,
                             const std::string &company,
                             const std::string &position);

    // Client retrieval methods
    std::shared_ptr<Client> getClientById(int clientId) const;
    std::vector<std::shared_ptr<Client>> getAllClients() const;
    std::vector<std::shared_ptr<Client>> searchClientsByName(const std::string &name) const;
    std::vector<std::shared_ptr<Client>> searchClientsByCompany(const std::string &company) const;
    std::vector<std::shared_ptr<Client>> getClientsInterestedInModel(const std::string &aiModel) const;

    // Client progress tracking
    bool updateClientProgress(int clientId, const std::string &aiModel, int proficiencyLevel);
    std::map<std::string, int> getClientProficiencies(int clientId) const;

    // Client AI model management
    bool addClientInterest(int clientId, const std::string &aiModel);
    bool removeClientInterest(int clientId, const std::string &aiModel);

    // Client session management
    bool updateClientSessionInfo(int clientId, const std::string &sessionDate);
    int getClientCompletedSessions(int clientId) const;

    // Client budget management
    bool updateClientBudget(int clientId, double amount, bool isAddition = true);
    double getClientBudget(int clientId) const;

    // Analytics methods
    std::map<std::string, int> getPopularAIModels() const;
    double getAverageClientSessions() const;
    std::vector<std::shared_ptr<Client>> getTopClients(int count) const;
};

#endif // CLIENT_SERVICE_H