#include "Logger.h"

int main() {
    Logger& logger = Logger::getInstance();

    logger.setLogFile("./xyz.txt");

    logger.setLogLevel(LogLevel::INFO);
    logger.log("Ustawiono poziom logowania na INFO 1", LogLevel::INFO);
    logger.log("Start aplikacji 1", LogLevel::INFO);
    logger.log("To jest ostrzeżenie! 1", LogLevel::WARNING);
    logger.log("Wystąpił błąd krytyczny! 1", LogLevel::ERROR);
    logger.log("Tryb debugowania 1", LogLevel::DEBUG);
    
    logger.setLogLevel(LogLevel::WARNING);
    logger.log("Ustawiono poziom logowania na WARNING 2", LogLevel::WARNING);
    logger.log("Start aplikacji 2", LogLevel::INFO);
    logger.log("To jest ostrzeżenie! 2", LogLevel::WARNING);
    logger.log("Wystąpił błąd krytyczny! 2", LogLevel::ERROR);
    logger.log("Tryb debugowania 2", LogLevel::DEBUG);

    logger.setLogLevel(LogLevel::ERROR);
    logger.log("Ustawiono poziom logowania na ERROR 3", LogLevel::ERROR);
    logger.log("Start aplikacji 3", LogLevel::INFO);
    logger.log("To jest ostrzeżenie! 3", LogLevel::WARNING);
    logger.log("Wystąpił błąd krytyczny! 3", LogLevel::ERROR);
    logger.log("Tryb debugowania 3", LogLevel::DEBUG);
    
    logger.setLogLevel(LogLevel::DEBUG);
    logger.log("Ustawiono poziom logowania na DEBUG 4", LogLevel::DEBUG);
    logger.log("Start aplikacji 4", LogLevel::INFO);
    logger.log("To jest ostrzeżenie! 4", LogLevel::WARNING);
    logger.log("Wystąpił błąd krytyczny! 4", LogLevel::ERROR);
    logger.log("Tryb debugowania 4", LogLevel::DEBUG);
    
    return 0;
}