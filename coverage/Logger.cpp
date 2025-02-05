#include "Logger.h"
#include <ctime>
#include <filesystem>

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

Logger::Logger() {
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::setLogFile(const std::string& filename) {


    if (logFile.is_open()) {
        logFile.close();
    }
    logFile.open(pathToLogDir + filename, std::ios::app);
    logFilename = filename;
}

void Logger::close() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

//size on bytes
void Logger::setMaxSizeOfLog(const uintmax_t& size)
{
    maxSizeOfLogFile = size;
}

void Logger::setLogLevel(LogLevel level) {
    logLevel = level;
}

void Logger::setPathToLogDir(const std::string& path)
{
    if(!std::filesystem::exists(path))
    {
        try
        {
            std::filesystem::create_directory(path);
        }
        catch(std::exception& e)
        {
            std::cout << "Cannot create directory for logs\nError code: " << e.what(); //cerr narazie jako debug
        }
    }

    pathToLogDir = path;
}

void Logger::showOnlyOneLevel(bool state, LogLevel level)
{
    if(level != logLevel)
    {
        setLogLevel(level);
    }

    onlyOneLevel = state;
}

std::string Logger::getLogLevelString(LogLevel level)
{
    std::string result = "Unknown level !!";
    switch (level) {
        case LogLevel::ALL:         result = "ALL"; break;
        case LogLevel::DEBUG:       result = "DEBUG"; break;
        case LogLevel::SUCCESS:     result = "SUCCESS"; break;
        case LogLevel::CONFIG:      result = "CONFIG"; break;
        case LogLevel::SECURITY:    result = "SECURITY"; break;
        case LogLevel::NETWORK:     result = "NETWORK"; break;
        case LogLevel::RESOURCE:    result = "RESOURCE"; break;
        case LogLevel::INFO:        result = "INFO"; break;
        case LogLevel::NOTICE:      result = "NOTICE"; break;
        case LogLevel::WARNING:     result = "WARNING"; break;
        case LogLevel::ERROR:       result = "ERROR"; break;
        case LogLevel::CRITICAL:    result = "CRITICAL"; break;
        case LogLevel::FATAL_ERROR: result = "FATAL_ERROR"; break;
    }

    return result;
}

void Logger::log(const std::string& message, LogLevel level) {
    if(onlyOneLevel && level != LogLevel::ALL){
        if (level != logLevel) {
            return;
        }
    }
    else{
        if (level < logLevel) {
            return;
        }
    }

    std::lock_guard<std::mutex> lock(logMutex);
    std::time_t now = std::time(nullptr);
    char timestamp[20];
    std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    
    std::string levelStr = getLogLevelString(level);
    
    std::string logMessage = std::string("[") + timestamp + "] " + levelStr + ": " + message + "\n";
    
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

std::string Logger::currectLogFilename()
{
    return logFilename;
}

std::string Logger::logFileNameGenerator()
{
    std::time_t now = std::time(nullptr);
    char currentTimestamp[20];
    std::strftime(currentTimestamp, sizeof(currentTimestamp), "%Y_%m_%d-%H-%M", std::localtime(&now));

    std::string logName = ("Log_" + std::string(currentTimestamp) + "_" + std::to_string(suffix) + ".txt");

    if(std::filesystem::exists(pathToLogDir + logName)) 
    {
        suffix++; 
        logName = ("Log_" + std::string(currentTimestamp) + "_" + std::to_string(suffix) + ".txt");
    }
    else 
    {
        suffix = 0;
    }

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
        setLogFile(newFilename); // Utwórz nowy log o oryginalnej nazwie
    }
}