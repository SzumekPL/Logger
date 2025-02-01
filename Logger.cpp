#include "Logger.h"
#include <ctime>
#include <filesystem>

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

Logger::Logger() {
    std::time_t now = std::time(nullptr);
    char currentTimestamp[20];
    std::strftime(currentTimestamp, sizeof(currentTimestamp), "%Y_%m_%d-%H-%M", std::localtime(&now));
    lastTimestamp = currentTimestamp;

    logFilename = "default_log.txt"; // Domyślna nazwa logów
    setLogFile(logFilename);
}

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
    logFilename = filename;
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
    

    rotateLogFile();
}

void Logger::setLogFileSizeLimit(const uintmax_t& size) // size in bytes
{
    if(maxSizeOfLogFile != size) 
    {
        maxSizeOfLogFile = size;
        //std::cout << "Change max size of file to:" << size;
    }
}

std::string Logger::logFileNameGenerator()
{
    std::time_t now = std::time(nullptr);
    char currentTimestamp[20];
    std::strftime(currentTimestamp, sizeof(currentTimestamp), "%Y_%m_%d-%H-%M", std::localtime(&now));

    std::cout << (currentTimestamp == lastTimestamp) << " " << std::string(currentTimestamp) << " " << lastTimestamp << "\n";

    if(currentTimestamp == lastTimestamp) {suffix++;}
    else {suffix = 0; lastTimestamp = std::string(currentTimestamp);}

    std::string logName = ("Log_" + std::string(currentTimestamp) + "_" + std::to_string(suffix) + ".txt");
    return logName;
}

void Logger::rotateLogFile()
{
    if (!std::filesystem::exists(logFilename)) {
        return; // Nie ma pliku do rotacji
    }

    if (std::filesystem::file_size(logFilename) > maxSizeOfLogFile) {
        std::string newFilename = logFileNameGenerator();

        logFile.close(); // Zamknij plik przed zmianą
        std::filesystem::rename(logFilename, newFilename); // Przenieś stary plik logów
        setLogFile(logFilename); // Utwórz nowy log o oryginalnej nazwie
    }
}