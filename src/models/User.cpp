#include "include/models/User.h"

// Default constructor
User::User() : userId(0), username(""), password(""), firstName(""), lastName(""), email(""), phone("") {}

// Parameterized constructor
User::User(int userId, const std::string& username, const std::string& password,
           const std::string& firstName, const std::string& lastName,
           const std::string& email, const std::string& phone)
    : userId(userId), username(username), password(password), firstName(firstName),
      lastName(lastName), email(email), phone(phone) {}

// Getters
int User::getUserId() const { return userId; }
std::string User::getUsername() const { return username; }
std::string User::getPassword() const { return password; }
std::string User::getFirstName() const { return firstName; }
std::string User::getLastName() const { return lastName; }
std::string User::getEmail() const { return email; }
std::string User::getPhone() const { return phone; }

// Setters
void User::setUserId(int userId) { this->userId = userId; }
void User::setUsername(const std::string& username) { this->username = username; }
void User::setPassword(const std::string& password) { this->password = password; }
void User::setFirstName(const std::string& firstName) { this->firstName = firstName; }
void User::setLastName(const std::string& lastName) { this->lastName = lastName; }
void User::setEmail(const std::string& email) { this->email = email; }
void User::setPhone(const std::string& phone) { this->phone = phone; }

// Get full name
std::string User::getFullName() const {
    return firstName + " " + lastName;
}

// Display user info
void User::displayInfo() const {
    std::cout << "User ID: " << userId << std::endl;
    std::cout << "Name: " << getFullName() << std::endl;
    std::cout << "Username: " << username << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Phone: " << phone << std::endl;
}

// Output stream operator
std::ostream& operator<<(std::ostream& os, const User& user) {
    os << "User ID: " << user.userId << std::endl;
    os << "Username: " << user.username << std::endl;
    os << "Name: " << user.getFullName() << std::endl;
    os << "Email: " << user.email << std::endl;
    os << "Phone: " << user.phone << std::endl;
    return os;
}

// Input stream operator
std::istream& operator>>(std::istream& is, User& user) {
    std::cout << "Enter User ID: ";
    is >> user.userId;
    is.ignore(); // Clear newline character

    std::cout << "Enter Username: ";
    std::getline(is, user.username);

    std::cout << "Enter Password: ";
    std::getline(is, user.password);

    std::cout << "Enter First Name: ";
    std::getline(is, user.firstName);

    std::cout << "Enter Last Name: ";
    std::getline(is, user.lastName);

    std::cout << "Enter Email: ";
    std::getline(is, user.email);

    std::cout << "Enter Phone: ";
    std::getline(is, user.phone);

    return is;
}