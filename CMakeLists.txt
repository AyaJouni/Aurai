# Standard configuration first
cmake_minimum_required(VERSION 3.10)
project(AITutoringCRM VERSION 1.0)

# Set C++ standard (avoid duplicate settings)
set(CMAKE_CXX_STANDARD 17)  # httplib works better with C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)  # Disable MSVC security warnings

# Force OpenSSL paths (using your verified installation path)
set(OPENSSL_ROOT_DIR "C:/Program Files/OpenSSL-Win64")
set(OPENSSL_INCLUDE_DIR "${OPENSSL_ROOT_DIR}/include")
set(OPENSSL_CRYPTO_LIBRARY "${OPENSSL_ROOT_DIR}/lib/VC/x64/MDd/libcrypto.lib")
set(OPENSSL_SSL_LIBRARY "${OPENSSL_ROOT_DIR}/lib/VC/x64/MDd/libssl.lib")

# Verify OpenSSL files exist
if(NOT EXISTS "${OPENSSL_INCLUDE_DIR}/openssl/ssl.h")
    message(FATAL_ERROR "OpenSSL headers missing! Check installation at ${OPENSSL_ROOT_DIR}")
endif()

if(NOT EXISTS "${OPENSSL_SSL_LIBRARY}")
    message(FATAL_ERROR "OpenSSL libssl.lib missing! Expected at: ${OPENSSL_SSL_LIBRARY}")
endif()

if(NOT EXISTS "${OPENSSL_CRYPTO_LIBRARY}")
    message(FATAL_ERROR "OpenSSL libcrypto.lib missing! Expected at: ${OPENSSL_CRYPTO_LIBRARY}")
endif()

if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0601)
endif()

# Include directories
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${OPENSSL_INCLUDE_DIR}
)

# Add link directory for SQLite3
link_directories("${PROJECT_SOURCE_DIR}/lib")

# Directory creation
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/logs)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/data)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/webui)

# Source files
set(SOURCES
    main.cpp
    src/models/User.cpp
    src/models/Admin.cpp
    src/models/Tutor.cpp
    src/models/AIModel.cpp
    src/models/Client.cpp
    src/models/TutoringSession.cpp     
    src/models/LearningMaterial.cpp    
    src/services/AuthService.cpp
    src/services/AIModelService.cpp
    src/services/ClientService.cpp
    src/services/SimpleAPIServer.cpp   
    src/services/LearningMaterialService.cpp 
    src/services/TutorService.cpp      
    src/services/SessionService.cpp    
)

# Create the executable
add_executable(AITutoringCRM ${SOURCES})

# Now add target_link_libraries AFTER the add_executable command
target_link_libraries(AITutoringCRM PRIVATE sqlite3)

# Linking
if(WIN32)
    target_link_libraries(AITutoringCRM PRIVATE 
        wsock32 
        ws2_32
        crypt32
        "${OPENSSL_SSL_LIBRARY}"
        "${OPENSSL_CRYPTO_LIBRARY}"
    )
endif()

find_package(Threads REQUIRED)
target_link_libraries(AITutoringCRM PRIVATE Threads::Threads)

# Compiler options
if(MSVC)
    target_compile_options(AITutoringCRM PRIVATE /W4 /wd4267 /wd4244 /wd4996)
endif()

# Web UI setup
if(EXISTS "${CMAKE_SOURCE_DIR}/paste.txt")
    configure_file(paste.txt ${CMAKE_BINARY_DIR}/webui/index.html COPYONLY)
endif()

# Also copy the CSS and JS files if they exist
if(EXISTS "${CMAKE_SOURCE_DIR}/styles.css")
    configure_file(styles.css ${CMAKE_BINARY_DIR}/webui/styles.css COPYONLY)
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/app.js")
    configure_file(app.js ${CMAKE_BINARY_DIR}/webui/app.js COPYONLY)
endif()

message(STATUS "OpenSSL configured at: ${OPENSSL_ROOT_DIR}")
message(STATUS "OpenSSL SSL library: ${OPENSSL_SSL_LIBRARY}")
message(STATUS "OpenSSL Crypto library: ${OPENSSL_CRYPTO_LIBRARY}")
message(STATUS "Build configuration complete")