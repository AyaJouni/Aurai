// Exception.h
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <exception>

// Base exception class for the CRM system
class CRMException : public std::exception {
private:
    std::string message;
    
public:
    CRMException(const std::string& msg) : message(msg) {}
    
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Specific exception types
class AuthenticationException : public CRMException {
public:
    AuthenticationException(const std::string& msg) : CRMException("Authentication Error: " + msg) {}
};

class AuthorizationException : public CRMException {
public:
    AuthorizationException(const std::string& msg) : CRMException("Authorization Error: " + msg) {}
};

class ValidationException : public CRMException {
public:
    ValidationException(const std::string& msg) : CRMException("Validation Error: " + msg) {}
};

class FileException : public CRMException {
public:
    FileException(const std::string& msg) : CRMException("File Error: " + msg) {}
};

class DatabaseException : public CRMException {
public:
    DatabaseException(const std::string& msg) : CRMException("Database Error: " + msg) {}
};

class ClientException : public CRMException {
public:
    ClientException(const std::string& msg) : CRMException("Client Error: " + msg) {}
};

class TutorException : public CRMException {
public:
    TutorException(const std::string& msg) : CRMException("Tutor Error: " + msg) {}
};

class SessionException : public CRMException {
public:
    SessionException(const std::string& msg) : CRMException("Session Error: " + msg) {}
};

class AIModelException : public CRMException {
public:
    AIModelException(const std::string& msg) : CRMException("AI Model Error: " + msg) {}
};

class MaterialException : public CRMException {
public:
    MaterialException(const std::string& msg) : CRMException("Learning Material Error: " + msg) {}
};

#endif // EXCEPTION_H