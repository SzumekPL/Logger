#include "Logger.h"
#include <ctime>

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

Logger::Logger() {}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::setLogFile(const std::string& filename) {
    std::lock_guard<std::mutex> lock(logMutex);
    if (logFile.is_open()) {
        logFile.close();
    }
    logFile.open(filename, std::ios::app);
}

void Logger::setLogLevel(LogLevel level) {
    logLevel = level;
}

void Logger::log(const std::string& message, LogLevel level) {
    if (level < logLevel) {
        return;
    }
    
    std::lock_guard<std::mutex> lock(logMutex);
    std::time_t now = std::time(nullptr);
    char timestamp[20];
    std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    
    std::string levelStr;
    switch (level) {
        case LogLevel::INFO: levelStr = "INFO"; break;
        case LogLevel::WARNING: levelStr = "WARNING"; break;
        case LogLevel::ERROR: levelStr = "ERROR"; break;
        case LogLevel::DEBUG: levelStr = "DEBUG"; break;
    }
    
    std::string logMessage = std::string("[") + timestamp + "] " + levelStr + ": " + message + "\n";
    
    std::cout << logMessage;
    if (logFile.is_open()) {
        logFile << logMessage;
    }
}