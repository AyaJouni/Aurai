@echo off
echo Setting up AI Tutoring CRM System with Simple HTTP Server...

REM Create necessary directories if they don't exist
if not exist include\services mkdir include\services
if not exist src\services mkdir src\services
if not exist webui mkdir webui

REM Copy the httplib.h file to the project
copy httplib.h .

REM Copy the new API server files
copy include\services\SimpleAPIServer.h include\services\
copy src\services\SimpleAPIServer.cpp src\services\

REM Create build directory if it doesn't exist
if not exist build mkdir build
cd build

REM Configure with CMake
echo Configuring project with CMake...
cmake ..

REM Build the project
echo Building project...
cmake --build . --config Release

REM Go back to the root directory
cd ..

REM Deploy web interface
echo Setting up web interface...
if not exist webui mkdir webui
copy paste.txt webui\index.html
copy styles.css webui\styles.css
copy app.js webui\app.js



REM Start the application
echo Starting AI Tutoring CRM System...
echo The web interface will be available at http://localhost:8080
.\build\Release\AITutoringCRM.exe

pause