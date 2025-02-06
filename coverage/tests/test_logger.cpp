// test_logger.cpp
#include <gtest/gtest.h>
#include "../Logger.h"
#include <fstream>

// Test 1: Sprawdzenie zapisu do pliku
TEST(LoggerTest, WritesToFile) {
    Logger& logger = Logger::getInstance();
    std::string dirPath = "./tests_dir/test1/";
    std::string logName = "test_log.txt";

    logger.setPathToLogDir(dirPath);
    logger.setLogFile(logName);
    logger.setLogLevel(LogLevel::INFO);

    logger.log("Testowy log INFO", LogLevel::INFO);
    logger.close();

    std::ifstream logFile(dirPath + logName);
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

// Test 2: Sprawdzenie czy tworzy nowe foldery
TEST(LoggerTest, DirPathChanging) {
    Logger& logger = Logger::getInstance();
    std::string dirPath = "./tests_dir/test2/";
    std::string logName = "dir_log.txt";

    logger.setPathToLogDir(dirPath);
    logger.setLogFile(logName);
    logger.setLogLevel(LogLevel::INFO);

    logger.log("Testowy log INFO", LogLevel::INFO);
    logger.close();

    std::ifstream logFile(dirPath + logName);
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

    logger.setPathToLogDir("./");
}

// Test 3: Sprawdzenie rotacji plików logów
TEST(LoggerTest, LogRotation) {
    Logger& logger = Logger::getInstance();
    std::string dirPath = "./tests_dir/test3/";
    std::string logName = "rotation_log.txt";

    logger.setPathToLogDir(dirPath);
    logger.setLogFile(logName);
    logger.setMaxSizeOfLog(200); //size 200Bytes
    logger.setLogLevel(LogLevel::ALL);

    for(int i = 0; i < 10; ++i)
        logger.log("Testowa linijka numer: " + std::to_string(i), LogLevel::INFO);

    bool changedFile = (logger.currectLogFilename() != logName);
    bool rotationFileExist = std::filesystem::exists(dirPath + logger.currectLogFilename());

    logger.close();
    EXPECT_TRUE(changedFile) << "Nie zmieniono nazwy pliku w programie";
    EXPECT_TRUE(rotationFileExist) << "Nowy plik nie istnieje";
    logger.setMaxSizeOfLog( 10000 ); //size 10kbytes for future tests
}

// Test 4: Sprawdzenie poziomów logowania
TEST(LoggerTest, LogLevelFiltering) {
    Logger& logger = Logger::getInstance();
    std::string dirPath = "./tests_dir/test4/";
    std::string logName = "level_log.txt";

    logger.setPathToLogDir(dirPath);
    logger.setLogFile(logName);
    logger.setLogLevel(LogLevel::ERROR);  // Tylko ERROR powinien być logowany

    logger.log("Poziom informacji", LogLevel::INFO);
    logger.log("Poziom ostrzezenia", LogLevel::WARNING);
    logger.log("Poziom bledu", LogLevel::ERROR); // Tylko to powinno być w pliku

    logger.close();

    std::ifstream logFile(dirPath + logName);
    std::string line;
    bool foundError = false, foundInfo = false, foundWarning = false;
    
    if (!logFile.is_open()) {
        FAIL() << "Nie udało się otworzyć pliku logu!";
    }

    while (std::getline(logFile, line)) {
        if (line.find("Poziom informacji") != std::string::npos) foundInfo = true;
        if (line.find("Poziom ostrzezenia") != std::string::npos) foundWarning = true;
        if (line.find("Poziom bledu") != std::string::npos) foundError = true;
    }

    logFile.close();
    EXPECT_FALSE(foundInfo) << "INFO nie powinno być zapisane!";
    EXPECT_FALSE(foundWarning) << "WARNING nie powinien być zapisany!";
    EXPECT_TRUE(foundError) << "ERROR powinien być zapisany!";
}

// Test 5: Sprawdzenie zapisu tylko jednego typu
TEST(LoggerTest, writeOnlyWarning) {
    Logger& logger = Logger::getInstance();
    std::string dirPath = "./tests_dir/test5/";
    std::string logName = "onlyWarning_log.txt";

    logger.setPathToLogDir(dirPath);
    logger.setLogFile(logName);
    logger.showOnlyOneLevel(LogLevel::WARNING);

    logger.log("Testowy log INFO", LogLevel::INFO);
    logger.log("Testowy log WARNING", LogLevel::WARNING);
    logger.log("Testowy log CRITICAL", LogLevel::CRITICAL);
    logger.close();

    std::ifstream logFile(dirPath + logName);
    std::string line;
    
    if (!logFile.is_open()) {
        FAIL() << "Nie udało się otworzyć pliku logu!";
    }

    bool foundInfo = false, foundWarning = false, foundCritical = false;
    while (std::getline(logFile, line)) {
        if (line.find("Testowy log INFO") != std::string::npos) foundInfo = true;
        if (line.find("Testowy log WARNING") != std::string::npos) foundWarning = true;
        if (line.find("Testowy log CRITICAL") != std::string::npos) foundCritical = true;
    }

    logFile.close();
    EXPECT_FALSE(foundInfo) << "INFO nie powinno być zapisane!";
    EXPECT_FALSE(foundCritical) << "CRITICAL  nie powinno być zapisane!";
    EXPECT_TRUE(foundWarning) << "WARNING powinien być zapisany!";
}

// Test 6: Sprawdzenie czy getFilename zwraca poprawna wartosc
TEST(LoggerTest, getFilename) {
    Logger& logger = Logger::getInstance();
    std::string dirPath = "./tests_dir/test6/";
    std::string logName = "test_log.txt";

    logger.setPathToLogDir(dirPath);
    logger.setLogFile(logName);

    logger.close();

    bool saveName = (logName == logger.currectLogFilename());
    EXPECT_TRUE(saveName) << "LogFileName nie jest zgodny z ostatnim wybranym LogFilem";
}

// Test 7: Sprawdzenie czy można swobodnie zmieniać plik
TEST(LoggerTest, setMoreLogFiles) {
    Logger& logger = Logger::getInstance();
    std::string dirPath = "./tests_dir/test7/";
    std::string logName = "first_log.txt";
    std::string logName2 = "second_log.txt";

    logger.setPathToLogDir(dirPath);
    logger.setLogFile(logName);
    logger.setLogLevel(LogLevel::ALL);  
    logger.log("Poziom informacji", LogLevel::INFO);

    logger.setLogFile(logName2);
    logger.log("Poziom informacji", LogLevel::INFO);

    logger.close();

    std::ifstream logFile(dirPath + logName);
    std::string line;
    
    if (!logFile.is_open()) {
        FAIL() << "Nie udało się otworzyć pliku logu!";
    }

    bool foundInfo = false;
    while (std::getline(logFile, line)) {
        if (line.find("Poziom informacji") != std::string::npos) foundInfo = true;
    }

    logFile.close();

    std::ifstream logFile2(dirPath + logName2);
    if (!logFile2.is_open()) {
        FAIL() << "Nie udało się otworzyć pliku logu!";
    }

    bool foundInfo2 = false;
    while (std::getline(logFile2, line)) {
        if (line.find("Poziom informacji") != std::string::npos) foundInfo2 = true;
    }

    logFile2.close();

    EXPECT_TRUE(foundInfo) << "Info powinno byc zapisane!";
    EXPECT_TRUE(foundInfo2) << "Info powinno byc zapisane!";
}

// Test 8: Sprawdzenie dynamicznej zmiany patternu
TEST(LoggerTest, dynamicPatternChange) {
    Logger& logger = Logger::getInstance();
    std::string dirPath = "./tests_dir/test8/";
    std::string logName = "pattern_log.txt";

    logger.setPathToLogDir(dirPath);
    logger.setLogFile(logName);
    logger.setLogLevel(LogLevel::ALL);

    logger.setLogFormat("{level} : {message}");
    logger.log("Test szablonu 1", LogLevel::WARNING);

    logger.setLogFormat("[{time}] : {message} [{level}]");
    logger.log("Test szablonu 2", LogLevel::WARNING);

    logger.close();

    std::ifstream logFile(dirPath + logName);
    std::string line;
    
    if (!logFile.is_open()) {
        FAIL() << "Nie udało się otworzyć pliku logu!";
    }

    bool foundPattern1 = false, foundPattern2 = false, foundPattern3 = false;
    while (std::getline(logFile, line)) {
        if (line.find("WARNING : Test szablonu 1") != std::string::npos) foundPattern1 = true;
        if (line.find("Test szablonu 2") != std::string::npos) foundPattern2 = true;
        if (line.find("] : Test szablonu 2 [WARNING]") != std::string::npos) foundPattern3 = true;
    }

    EXPECT_TRUE(foundPattern1) << "Nie znaleziono pierwszego wpisu!";
    EXPECT_TRUE(foundPattern2) << "Nie znalezio drugiego wpisu";
    EXPECT_TRUE(foundPattern3) << "Nie zmieniono patternu";
}