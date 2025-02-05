#include "Logger.h"

int main() {
    Logger& logger = Logger::getInstance();
    std::string dirPath = "./tests_dir/test0/";
    std::string logName = "rotation_log.txt";

    logger.setPathToLogDir(dirPath);
    logger.setLogFile(logName);
    logger.setMaxSizeOfLog(200); //size 4KBytes //default buffor for most systems is 4KB 
    logger.setLogLevel(LogLevel::ALL);

    for(int i = 0; i < 4001; ++i)
        logger.log("Testowa linijka numer: " + std::to_string(i), LogLevel::INFO);

    bool changedFile = (logger.currectLogFilename() != logName);
    std::cout << changedFile;

    return 0;
}