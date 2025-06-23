#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

class Logger {
    
    public:
    Logger();
    
    enum LogType {
        INFO,
        WARNING,
        ERROR,
        DEBUG,
        SUCCESS
    };

    void print(LogType LogType, std::string message);
};

#endif