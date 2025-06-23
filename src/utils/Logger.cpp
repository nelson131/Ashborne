#include <iostream>
#include "Logger.h"

#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define PURPLE  "\033[35m"
#define RESET   "\033[0m"

Logger::Logger() {

}

void Logger::print(LogType LogType, std::string message){
    switch(LogType) {
        case INFO:
            std::cout << "[INFO] " << message << std::endl; 
            break;
        case WARNING:
            std::cout << YELLOW << "[WARNING] " << message << RESET  << std::endl;
            break;
        case ERROR:
            std::cout << RED << "[ERROR] " << message << RESET << std::endl;
            break;
        case DEBUG:
            std::cout << PURPLE << "[DEBUG] " << message << RESET << std::endl;
            break;
        case SUCCESS:
            std::cout << GREEN << "[SUCCESS] " << message << RESET << std::endl;
            break;
        default:
            break;
    }
}