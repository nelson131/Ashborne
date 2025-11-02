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
    static std::string findSpecial(std::string content);

    template<typename T>
    static T parse(std::string keyTitle, std::string keyMessage){
        std::ifstream file("resources/config.ini");
        std::string title = "[" + keyTitle + "]";
        std::string line;
        bool hasKey = false;
        while(getline(file, line)){
            if(line[0] == '#' && line.empty()) continue;
            if(line[0] == '['){
                hasKey = (line == title);
                continue;
            }
            if(hasKey){
                size_t pos = line.find("=");
                if(pos != std::string::npos){
                    std::string key = line.substr(0, pos);
                    if(key == keyMessage){
                        std::string value = line.substr(pos + 1);
                        std::stringstream str(value);
                        T res{};
                        str >> res;
                        if(str.fail()){
                            Logger::print(Logger::ERROR, "Failed to convert shit from config");
                            return T{};
                        }
                        return res;
                    }
                }
            }
        }
        Logger::print(Logger::ERROR, "Failed to find message from config: ", keyTitle, " | ", keyMessage);
        return T{};
    }
};

#endif