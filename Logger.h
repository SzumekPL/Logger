// Logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <mutex>
#include <string>
#include <memory>

// Definiujemy poziomy logowania
enum class LogLevel {
    INFO,
    WARNING,
    ERROR,
    DEBUG
};

class Logger {
public:
    static Logger& getInstance();
    void log(const std::string& message, LogLevel level);
    void setLogLevel(LogLevel level);
    void setLogFile(const std::string& filename);

private:
    Logger();  // Prywatny konstruktor (Singleton)
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::string logFileNameGenerator( );
    void rotateLogFile();

    unsigned int suffix = 0;

    std::string lastTimestamp = ""; // Timestamp ostatniego pliku
    unsigned int suffix = 0; // Suffix w razie potrzeby powtorzenia w tej samej minucie

    std::string logFilename; // nazwa pliku
    std::ofstream logFile; // strumień do otwartego pliku
    LogLevel logLevel = LogLevel::INFO; // poziom zabezpieczeń
    std::mutex logMutex; // mutex przeciw konfliktą w wielowatkowości
};

#endif // LOGGER_H