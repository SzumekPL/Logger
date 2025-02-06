#include "Logger.h"

int main() {
    Logger& logger = Logger::getInstance();
    std::string dirPath = "./tests_dir/test0/";
    std::string logName = "rotation_log.txt";

    logger.setPathToLogDir(dirPath);
    logger.setLogFile(logName);
    logger.setMaxSizeOfLog(2000); //size 4KBytes //default buffor for most systems is 4KB 
    logger.setLogLevel(LogLevel::ALL);

    for(int i = 0; i < 10; ++i)
        logger.log("Testowa linijka numer: " + std::to_string(i), LogLevel::INFO);

    logger.setLogFormat("{time: {time}, message: {message}, level: {level}}");
    for(int i = 10; i < 20; ++i)
        logger.log("Testowa straszna linijka numer: " + std::to_string(i), LogLevel::WARNING);

    return 0;
}