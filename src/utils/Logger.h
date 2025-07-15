#ifndef LOGGER_H
#define LOGGER_H

#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define PURPLE  "\033[35m"
#define RESET   "\033[0m"

#include <iostream>
#include <sstream>

class Logger {
    
    public:
    Logger();
    
    enum Type {
        INFO,
        WARNING,
        ERROR,
        DEBUG,
        SUCCESS
    };

    template<typename... Targs>
    static void print(Type logType, const Targs&... args){
        std::string prefix;
        std::ostringstream str;
        (str << ... << args);

        switch(logType){
            case INFO:
                prefix = std::string(BLUE) + "[INFO] " + RESET;
                break;
            case WARNING:
                prefix = std::string(YELLOW) + "[WARNING] " + RESET;
                break;
            case ERROR:
                prefix = std::string(RED) + "[ERROR] " + RESET;
                break;
            case DEBUG:
                prefix = std::string(PURPLE) + "[DEBUG] " + RESET;
                break;
            case SUCCESS:
                prefix = std::string(GREEN) + "[SUCCESS] " + RESET;
        }

        std::cout << prefix << str.str() << std::endl;
    }
};

#endif