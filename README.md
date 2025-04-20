# AI Tutoring Center CRM System

A comprehensive Customer Relationship Management system designed specifically for teaching AI to clients, developed as a university project at Lebanese American University under the MIT License.

## Project Overview

This C++ application manages clients seeking to learn about AI, schedules tutoring sessions, tracks client progress with different AI models, and organizes educational resources. The system follows object-oriented programming principles and provides a role-based access system for administrators and tutors.

The application provides both a console interface and a web-based UI through a built-in API server, offering flexible ways to interact with the system.

## Features

- **Client Management**
  - Register and manage client profiles
  - Track client progress with different AI models
  - Search and filter client records
  - Manage client budgets and payment tracking

- **Session Management**
  - Schedule AI tutoring sessions
  - Manage remote and in-person sessions
  - Record learning outcomes and feedback
  - View session history
  - Support for session cancellation and rescheduling

- **AI Model Management**
  - Catalog different AI models for teaching
  - Track model details, capabilities, and complexity
  - Match clients with appropriate AI learning paths
  - Manage model deprecation and updates

- **User Management**
  - Support for multiple user roles (Admin, Tutor)
  - Role-based access control
  - Secure authentication
  - Tutor specialization and expertise tracking

- **Learning Materials Management**
  - Create and organize learning resources
  - Categorize by type, format, and difficulty
  - Tag system for easy searching
  - Track material usage and ratings

- **Reporting**
  - Generate student progress reports
  - Analyze tutoring effectiveness
  - Track usage patterns and popular subjects
  - Financial reporting for revenue tracking

- **Data Persistence**
  - Save and load data from files
  - Option for SQLite database integration
  - Maintain data integrity

- **Web Interface**
  - Modern, responsive dashboard
  - Client, tutor, session, and material management
  - Visualized statistics
  - Cross-platform accessibility

## Technical Implementation

- Object-Oriented Design with inheritance and polymorphism
- Operator overloading for streamlined I/O
- STL containers and algorithms
- Custom exception handling
- File I/O and database integration
- JSON-based RESTful API
- Separation of interface and implementation
- Modern web interface with vanilla JavaScript

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
│   ├── services/               # Business logic services
│   │   ├── AuthService.h       # Authentication and user management
│   │   ├── ClientService.h     # Client-related operations
│   │   ├── AIModelService.h    # AI model management
│   │   ├── SessionService.h    # Session scheduling and management
│   │   ├── LearningMaterialService.h # Material management
│   │   ├── ReportService.h     # Report generation
│   │   ├── FileService.h       # Data persistence
│   │   └── SimpleAPIServer.h   # Web API endpoint handling
│   └── utils/                  # Utility classes
│       ├── Logger.h            # Logging functionality
│       ├── Exception.h         # Custom exceptions
│       ├── Validation.h        # Input validation
│       ├── Menu.h              # Console menu system
│       └── DatabaseManager.h   # Database connectivity
├── src/                        # Implementation files
│   ├── models/                 # Model implementations
│   ├── services/               # Service implementations
│   └── utils/                  # Utility implementations
├── data/                       # Data storage
│   ├── clients.json            # Client data
│   ├── tutors.json             # Tutor data
│   ├── sessions.json           # Session data
│   ├── materials.json          # Learning materials data
│   └── users.dat               # User authentication data
├── webui/                      # Web interface
│   ├── index.html              # Main dashboard HTML
│   ├── styles.css              # CSS styling
│   └── app.js                  # Frontend JavaScript
├── docs/                       # Project documentation
├── CMakeLists.txt              # Build configuration
├── build_and_run.bat           # Windows build script
└── LICENSE                     # MIT License
```

## Getting Started

### Prerequisites

- C++ compiler with C++11 support or later
- CMake (version 3.10 or higher)
- OpenSSL for secure API connections (for web interface)

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

   Alternatively, on Windows, you can use the provided batch file to build and run:
   ```
   .\build_and_run.bat
   ```

### Using the Web Interface

1. After starting the application, the built-in web server will run on port 8080
2. Open a browser and navigate to `http://localhost:8080`
3. The default admin credentials are:
   - Username: admin
   - Password: admin123

## API Endpoints

The system provides a RESTful API that can be accessed at `http://localhost:8080/api/`:

- `/clients` - Client management
- `/tutors` - Tutor management
- `/sessions` - Session management
- `/materials` - Learning materials management
- `/aimodels` - AI model management

## Usage

### Console Interface

1. Launch the application
2. Log in with your credentials
3. Navigate the menu system to access various features
4. Follow on-screen prompts for specific operations

### Web Interface

1. Access the dashboard at `http://localhost:8080`
2. Use the navigation menu to switch between different sections
3. Manage clients, tutors, sessions, and learning materials
4. View statistics on the dashboard

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