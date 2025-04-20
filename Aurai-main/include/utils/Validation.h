// Validation.h
#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>
#include <regex>
#include "Exception.h"

class Validation {
public:
    // Email validation
    static bool isValidEmail(const std::string& email) {
        const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
        return std::regex_match(email, pattern);
    }
    
    // Phone validation (accepts formats like: 123-456-7890, (123) 456-7890, 123.456.7890)
    static bool isValidPhone(const std::string& phone) {
        const std::regex pattern("\\(?\\d{3}\\)?[-. ]?\\d{3}[-. ]?\\d{4}");
        return std::regex_match(phone, pattern);
    }
    
    // Date validation (format: YYYY-MM-DD)
    static bool isValidDate(const std::string& date) {
        const std::regex pattern("\\d{4}-\\d{2}-\\d{2}");
        if (!std::regex_match(date, pattern)) {
            return false;
        }
        
        // Extract year, month, and day
        int year = std::stoi(date.substr(0, 4));
        int month = std::stoi(date.substr(5, 2));
        int day = std::stoi(date.substr(8, 2));
        
        // Check month
        if (month < 1 || month > 12) {
            return false;
        }
        
        // Check day based on month
        int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        
        // Adjust for leap year
        if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
            daysInMonth[2] = 29;
        }
        
        return (day >= 1 && day <= daysInMonth[month]);
    }
    
    // Time validation (format: HH:MM, 24-hour)
    static bool isValidTime(const std::string& time) {
        const std::regex pattern("([01]?[0-9]|2[0-3]):[0-5][0-9]");
        return std::regex_match(time, pattern);
    }
    
    // Integer validation
    static bool isInteger(const std::string& str) {
        if (str.empty()) {
            return false;
        }
        
        size_t i = 0;
        if (str[0] == '-' || str[0] == '+') {
            i = 1;
            if (str.size() == 1) {
                return false;
            }
        }
        
        for (; i < str.size(); i++) {
            if (!std::isdigit(str[i])) {
                return false;
            }
        }
        
        return true;
    }
    
    // Floating point validation
    static bool isDouble(const std::string& str) {
        if (str.empty()) {
            return false;
        }
        
        char* end = nullptr;
        std::strtod(str.c_str(), &end);
        
        return end != str.c_str() && *end == '\0';
    }
    
    // Non-empty string validation
    static bool isNonEmpty(const std::string& str) {
        return !str.empty() && str.find_first_not_of(' ') != std::string::npos;
    }
    
    // Alphanumeric validation
    static bool isAlphanumeric(const std::string& str) {
        return std::all_of(str.begin(), str.end(), [](char c) {
            return std::isalnum(c);
        });
    }
    
    // Range validation
    template<typename T>
    static bool isInRange(const T& value, const T& min, const T& max) {
        return value >= min && value <= max;
    }
    
    // Validate input with custom error message
    template<typename T>
    static T validateInput(const T& input, bool (*validator)(const T&), const std::string& errorMsg) {
        if (!validator(input)) {
            throw ValidationException(errorMsg);
        }
        return input;
    }
};

#endif // VALIDATION_H