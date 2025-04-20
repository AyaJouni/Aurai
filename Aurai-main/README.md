# AI Tutoring Center CRM System

A comprehensive Customer Relationship Management system designed specifically for teaching AI to clients, developed as a university project at Lebanese American University under the MIT License.

## Project Overview

This C++ console application helps manage clients seeking to learn about AI, schedule tutoring sessions, track client progress with different AI models, and organize educational resources. The system follows object-oriented programming principles and provides a role-based access system for administrators and tutors.

## Features

- **Client Management**
  - Register and manage client profiles
  - Track client progress with different AI models
  - Search and filter client records

- **Session Management**
  - Schedule AI tutoring sessions
  - Record learning outcomes and feedback
  - View session history

- **AI Model Management**
  - Catalog different AI models for teaching
  - Track model details, capabilities, and complexity
  - Match clients with appropriate AI learning paths

- **User Management**
  - Support for multiple user roles (Admin, Tutor)
  - Role-based access control
  - Secure authentication

- **Reporting**
  - Generate student progress reports
  - Analyze tutoring effectiveness
  - Track usage patterns and popular subjects

- **Data Persistence**
  - Save and load data from files
  - Maintain data integrity

## Technical Implementation

- Object-Oriented Design with inheritance and polymorphism
- Operator overloading for streamlined I/O
- STL containers and algorithms
- Custom exception handling
- File I/O for data persistence
- Separation of interface and implementation

## Project Structure

```
AITutoringCRM/
├── include/                     # Header files
│   ├── models/                  # Data models
│   │   ├── User.h              # Base abstract class for all users
│   │   ├── Admin.h             # Admin user specialized for AI tutoring
│   │   ├── Tutor.h             # Tutor with AI specializations
│   │   ├── Client.h            # Client who wants to learn about AI
│   │   ├── AIModel.h           # Information about AI models being taught
│   │   ├── TutoringSession.h   # Session between tutor and client
│   │   └── LearningMaterial.h  # Resources for teaching AI
│   ├── services/                # Business logic
│   └── utils/                   # Utility classes
├── src/                         # Implementation files
├── data/                        # Data storage
├── docs/                        # Project documentation
└── CMakeLists.txt               # Build configuration
```

## Getting Started

### Prerequisites

- C++ compiler with C++11 support or later
- CMake (version 3.10 or higher)

### Building the Project

1. Clone the repository
   ```
   git clone https://github.com/farengi/Aurai
   cd AITutoringCRM
   ```

2. Create a build directory
   ```
   mkdir build
   cd build
   ```

3. Configure and build
   ```
   cmake ..
   make
   ```

4. Run the application
   ```
   ./AITutoringCRM
   ```

## Usage

1. Launch the application
2. Log in with your credentials
3. Navigate the menu system to access various features
4. Follow on-screen prompts for specific operations

## Team Members

- **Farah Al-Nassar** - Project Manager - Responsible for planning and scheduling
- **Aya Jouni** - Presales Engineer - Defined functional and non-functional requirements
- **Lynne Al-Safawi** - Solutions Architect - Designed system architecture and UML diagrams
- **All Members** - Technical Experts - Implemented the system based on specifications

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- Lebanese American University for the project opportunity
- All team members for their contributions
