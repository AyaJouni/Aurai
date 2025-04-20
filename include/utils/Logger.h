// Logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <mutex>
#include <sstream>

// Use a simple enum instead of enum class
enum LogLevel
{
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_CRITICAL
};

class Logger
{
private:
    std::string logFilename;
    LogLevel minLevel;
    std::ofstream logFile;

    // Private constructor for singleton pattern
    Logger(const std::string &filename, LogLevel level = LOG_INFO)
        : logFilename(filename), minLevel(level)
    {
        logFile.open(filename, std::ios::app);
        if (!logFile.is_open())
        {
            std::cerr << "Failed to open log file: " << filename << std::endl;
        }
    }

    // Get current timestamp as string
    std::string getCurrentTimestamp() const;

    // Convert LogLevel to string
    std::string logLevelToString(LogLevel level) const
    {
        switch (level)
        {
        case LOG_DEBUG:
            return "DEBUG";
        case LOG_INFO:
            return "INFO";
        case LOG_WARNING:
            return "WARNING";
        case LOG_ERROR:
            return "ERROR";
        case LOG_CRITICAL:
            return "CRITICAL";
        default:
            return "UNKNOWN";
        }
    }

public:
    // Delete copy constructor and assignment operator
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

    // Singleton instance accessor
    static Logger &getInstance()
    {
        static Logger instance("logs/crm.log");
        return instance;
    }

    // Destructor
    ~Logger()
    {
        if (logFile.is_open())
        {
            logFile.close();
        }
    }

    // Set minimum log level
    void setMinLevel(LogLevel level)
    {
        minLevel = level;
    }

    // Log a message
    void log(LogLevel level, const std::string &message);

    // Convenience methods for different log levels
    void debug(const std::string &message)
    {
        log(LOG_DEBUG, message);
    }

    void info(const std::string &message)
    {
        log(LOG_INFO, message);
    }

    void warning(const std::string &message)
    {
        log(LOG_WARNING, message);
    }

    void error(const std::string &message)
    {
        log(LOG_ERROR, message);
    }

    void critical(const std::string &message)
    {
        log(LOG_CRITICAL, message);
    }

    // Thread-safe method to get mutex
    static std::mutex &getMutex()
    {
        static std::mutex mutex;
        return mutex;
    }
};

// Move implementation to separate function to avoid potential inline issues
inline std::string Logger::getCurrentTimestamp() const
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

inline void Logger::log(LogLevel level, const std::string &message)
{
    if (level < minLevel)
    {
        return;
    }

    std::lock_guard<std::mutex> lock(getMutex());

    if (logFile.is_open())
    {
        logFile << getCurrentTimestamp() << " [" << logLevelToString(level) << "] "
                << message << std::endl;
        logFile.flush();
    }

    // Also print to console for higher levels
    if (level >= LOG_WARNING)
    {
        std::cout << "[" << logLevelToString(level) << "] " << message << std::endl;
    }
}

#endif // LOGGER_H