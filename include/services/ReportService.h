// ReportService.h
#ifndef REPORT_SERVICE_H
#define REPORT_SERVICE_H

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "../models/Client.h"
#include "../models/Tutor.h"
#include "../models/TutoringSession.h"
#include "../models/AIModel.h"

// Forward declarations of other services
class ClientService;
class TutorService;
class SessionService;
class AIModelService;
class LearningMaterialService;

class ReportService {
private:
    // References to other services for data access
    std::shared_ptr<ClientService> clientService;
    std::shared_ptr<TutorService> tutorService;
    std::shared_ptr<SessionService> sessionService;
    std::shared_ptr<AIModelService> aiModelService;
    std::shared_ptr<LearningMaterialService> materialService;
    
    // Helper methods
    std::string getCurrentDate() const;
    std::string generateReportFilename(const std::string& reportType) const;
    bool saveReportToFile(const std::string& content, const std::string& filename) const;
    
public:
    // Constructor and Destructor
    ReportService(std::shared_ptr<ClientService> clientService,
                 std::shared_ptr<TutorService> tutorService,
                 std::shared_ptr<SessionService> sessionService,
                 std::shared_ptr<AIModelService> aiModelService,
                 std::shared_ptr<LearningMaterialService> materialService);
    ~ReportService();
    
    // Financial reports
    std::string generateRevenueReport(const std::string& startDate, const std::string& endDate) const;
    std::string generateClientSpendingReport(int clientId) const;
    std::string generateTutorEarningsReport(int tutorId) const;
    std::string generateMonthlyFinancialSummary(int month, int year) const;
    
    // Client reports
    std::string generateClientProgressReport(int clientId) const;
    std::string generateAllClientsReport() const;
    std::string generateClientAttendanceReport(int clientId) const;
    
    // Tutor reports
    std::string generateTutorPerformanceReport(int tutorId) const;
    std::string generateTutorScheduleReport(int tutorId) const;
    std::string generateTutorSpecializationReport() const;
    
    // Session reports
    std::string generateSessionSummaryReport(int sessionId) const;
    std::string generateUpcomingSessionsReport() const;
    std::string generateCompletedSessionsReport(const std::string& startDate, const std::string& endDate) const;
    
    // AI Model reports
    std::string generatePopularAIModelsReport() const;
    std::string generateAIModelUsageReport(int modelId) const;
    std::string generateTutorAIExpertiseReport() const;
    
    // Learning materials reports
    std::string generatePopularMaterialsReport() const;
    std::string generateMaterialsByAIModelReport(int modelId) const;
    
    // Analytics reports
    std::string generateClientRetentionReport() const;
    std::string generateBusinessGrowthReport() const;
    std::string generateTrendAnalysisReport() const;
    
    // Custom report
    std::string generateCustomReport(const std::string& reportType, 
                                   const std::map<std::string, std::string>& parameters) const;
};

#endif // REPORT_SERVICE_H