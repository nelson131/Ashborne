#ifndef CONFIG_H
#define CONFIG_H

#include "Logger.h"
#include <iostream>
#include <fstream>
#include <sstream>

class Config {
    
    public:
    Config();
    void init();

    template<typename T>
    static T parse(std::string keyTitle, std::string keyMessage){
        std::ifstream file("resources/config.ini");
        std::string title = "[" + keyTitle + "]";
        std::string message = keyMessage + "=";
        std::string line;
        bool hasKey = false;
        while(getline(file, line)){
            if(line[0] == '#' && line.empty()) continue;
            if(line[0] == '['){
                hasKey = (line == title);
            } else if(hasKey && line.rfind(message, 0) == 0){
                std::istringstream str(line.substr(message.length()));
                T res;
                str >> res;
                return res;
            }
        }
        Logger::print(Logger::ERROR, "Failed to find message from config");
        return T{};
    }
};

#endif