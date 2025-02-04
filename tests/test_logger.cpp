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
    logger.setLogLevel(LogLevel::INFO);

    for (int i = 0; i < 100; ++i) {
        logger.log("Testowy wpis do rotacji", LogLevel::INFO);
    }
    
    bool changedFile = (logger.currectLogFilename() != "rotation_test.txt");

    EXPECT_TRUE(changedFile) << "Plik logów nie został poprawnie utworzony!";
    logger.close();
    logger.setMaxSizeOfLog( 10000 ); //size 10kbytes for future tests
}

// Test 3: Sprawdzenie poziomów logowania
TEST(LoggerTest, LogLevelFiltering) {
    Logger& logger = Logger::getInstance();
    logger.setLogFile("level_test.txt");
    logger.setLogLevel(LogLevel::ERROR);  // Tylko ERROR powinien być logowany

    logger.log("Poziom informacji", LogLevel::INFO);
    logger.log("Poziom ostrzezenia", LogLevel::WARNING);
    logger.log("ERROR", LogLevel::ERROR); // Tylko to powinno być w pliku

    logger.close();

    std::ifstream logFile("level_test.txt");
    std::string line;
    bool foundError = false, foundInfo = false, foundWarning = false;
    
    if (!logFile.is_open()) {
        FAIL() << "Nie udało się otworzyć pliku logu!";
    }

    while (std::getline(logFile, line)) {
        if (line.find("Poziom informacji") != std::string::npos) foundInfo = true;
        if (line.find("Poziom ostrzezenia") != std::string::npos) foundWarning = true;
        if (line.find("ERROR") != std::string::npos) foundError = true;
    }

    logFile.close();
    EXPECT_FALSE(foundInfo) << "INFO nie powinno być zapisane!";
    EXPECT_FALSE(foundWarning) << "WARNING nie powinien być zapisany!";
    EXPECT_TRUE(foundError) << "ERROR powinien być zapisany!";
}