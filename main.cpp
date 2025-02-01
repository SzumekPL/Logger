#include "Logger.h"

int main() {
    Logger& logger = Logger::getInstance();
    logger.setLogFile("logs.txt");
    logger.setLogLevel(LogLevel::INFO);

    logger.log("Start aplikacji", LogLevel::INFO);
    logger.log("To jest ostrzeżenie!", LogLevel::WARNING);
    logger.log("Wystąpił błąd krytyczny!", LogLevel::ERROR);
    logger.log("Tryb debugowania", LogLevel::DEBUG);
    
    return 0;
}