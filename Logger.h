// Logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <mutex>
#include <string>
#include <memory>

// Definiujemy poziomy logowania
// NIE ZAPOMNIJ PO MODYFIKACJI SPRAWDZIĆ 
// getLogLevelString() !!
enum class LogLevel {
    ALL, //0

    // Log levels only for information
    DEBUG, // -6
    SUCCESS, // -5
    CONFIG,  // -4
    SECURITY, // -3
    NETWORK,  // -2
    RESOURCE, // -1

    // Danger level of logs
    INFO, //1
    NOTICE, //2
    WARNING, //3
    ERROR, //4
    CRITICAL, // 5
    FATAL_ERROR, // 6
};

class Logger {
public:
    static Logger& getInstance();
    void log(const std::string& message, LogLevel level);
    void setLogLevel(LogLevel level);
    void setLogFile(const std::string& filename);
    void setLogFileSizeLimit(const uintmax_t& size); // size in bytes
    void setPathToLogDir(const std::string& path);
    void setMaxSizeOfLog(const uintmax_t& size);
    void showOnlyOneLevel(bool state, LogLevel level);

    std::string getLogLevelString(LogLevel level);

    std::string currectLogFilename(); 

    void close();

private:
    Logger();  // Prywatny konstruktor (Singleton)
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::string logFileNameGenerator( );
    void rotateLogFile();

    uintmax_t maxSizeOfLogFile = 1000; //1KB

    bool onlyOneLevel = false;
    std::string pathToLogDir = "./";
    unsigned int suffix = 0; // Suffix w razie potrzeby powtorzenia w tej samej minucie

    std::string logFilename; // nazwa pliku
    std::ofstream logFile; // strumień do otwartego pliku
    LogLevel logLevel = LogLevel::INFO; // poziom zabezpieczeń
    std::mutex logMutex; // mutex przeciw konfliktą w wielowatkowości
};

#endif // LOGGER_H