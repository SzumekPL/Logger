#include "Logger.h"
#include <ctime>
#include <filesystem>

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

Logger::Logger() {
    logPattern = "[{time}] {level}: {message}";
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
    onlyOneLevel = false;
}

void Logger::setPathToLogDir(const std::string& path)
{
    if(!std::filesystem::exists(path))
    {
        try
        {
            std::filesystem::create_directories(path);
        }
        catch(std::exception& e)
        {
            std::cout << "Cannot create directory for logs\nError code: " << e.what(); //cerr narazie jako debug
        }
    }

    pathToLogDir = path;
}

void Logger::showOnlyOneLevel(LogLevel level)
{
    if(level != logLevel)
    {
        setLogLevel(level);
    }

    onlyOneLevel = true;
}

std::string getTimestamp()
{
    std::time_t now = std::time(nullptr);
    char timestamp[20];
    std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

    return std::string( timestamp );
}

void Logger::setLogFormat(std::string pattern)
{
    logPattern = pattern;
}

std::string Logger::replaceToPattern(std::string message, std::string level)
{
    std::string result = logPattern;
    
    size_t pos = result.find("{time}");
    if (pos != std::string::npos) {
        result.replace(pos, 6, getTimestamp());
    }
    
    pos = result.find("{level}");
    if (pos != std::string::npos) {
        result.replace(pos, 7, level);
    }

    pos = result.find("{message}");
    if (pos != std::string::npos) {
        result.replace(pos, 9, message);
    }
    
    return result;
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

    std::lock_guard<std::mutex> lock(logMutex);
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
    std::string levelStr = getLogLevelString(level);
    std::string timestamp = getTimestamp();
    
    std::string logMessage = replaceToPattern(message, levelStr);
    
    if (logFile.is_open()) {
        logFile << logMessage;
        logFile << std::endl;
    }
    else{
        std::cout << "I cannot write into file!!!";
    }

    rotateLogFile();
}

std::string Logger::currectLogFilename()
{
    return logFilename;
}

std::string Logger::logFileNameGenerator()
{
    std::string timestamp = getTimestamp();

    std::string logName = ("Log_" + std::string(timestamp) + "_" + std::to_string(suffix) + ".txt");

    if(std::filesystem::exists(pathToLogDir + logName)) 
    {
        suffix++; 
        logName = ("Log_" + std::string(timestamp) + "_" + std::to_string(suffix) + ".txt");
    }
    else 
    {
        suffix = 0;
    }

    return logName;
}

void Logger::rotateLogFile()
{
    if (!std::filesystem::exists(pathToLogDir + logFilename)) {
        std::cout << pathToLogDir + logFilename << "doesnt exist";
        return; // Nie ma pliku do rotacji
    }

    uintmax_t fileSize = 0;
    try
    {
        fileSize = std::filesystem::file_size(pathToLogDir + logFilename);
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
    
    if (fileSize > 0) 
    {
        if(fileSize > maxSizeOfLogFile)
        {
            std::string newFilename = logFileNameGenerator();
            setLogFile(newFilename); // Utwórz nowy log o oryginalnej nazwie
        }
    }
}