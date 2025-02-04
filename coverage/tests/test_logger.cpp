// test_logger.cpp
#include <gtest/gtest.h>
#include "../Logger.h"
#include <fstream>

// Test 1: Sprawdzenie zapisu do pliku
TEST(LoggerTest, WritesToFile) {
    Logger& logger = Logger::getInstance();
    logger.setLogFile("test_log.txt");
    logger.setLogLevel(LogLevel::INFO);

    logger.log("Testowy log INFO", LogLevel::INFO);
    logger.close();

    std::ifstream logFile("test_log.txt");
    std::string line;
    bool found = false;
    
    if (!logFile.is_open()) {
        FAIL() << "Nie udało się otworzyć pliku logu!";
    }

    while (std::getline(logFile, line)) {
        if (line.find("Testowy log INFO") != std::string::npos) {
            found = true;
            break;
        }
    }

    logFile.close();
    EXPECT_TRUE(found) << "Nie znaleziono wpisu w logu!";
}

// Test 2: Sprawdzenie rotacji plików logów
TEST(LoggerTest, LogRotation) {
    Logger& logger = Logger::getInstance();
    logger.setLogFile("rotation_test.txt");
    logger.setMaxSizeOfLog( 200 ); //size 200bytes


    for (int i = 0; i < 5; ++i) {
        logger.log("Testowy wpis do rotacji", LogLevel::INFO);
    }
    
    std::ifstream logFile("rotation_test.txt");
    EXPECT_TRUE(logFile.good()) << "Plik logów nie został poprawnie utworzony!";
    logFile.close();
}