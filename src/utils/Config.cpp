#include <iostream>
#include <fstream>
#include "Config.h"

Config::Config(){

}

void Config::init(){
    std::ifstream file("resources/config.ini");
    if(file.is_open()){
        logger.print(logger.INFO, "Config file already exist");
    } else {
        std::ofstream cfg("resources/config.ini");
        cfg << "[game_info]\n";
        cfg << "name=\n";
        cfg << "version=\n";
        cfg << "width=\n";
        cfg << "height=\n";
        logger.print(logger.INFO, "Config file has been created");
    }
}

std::string Config::parse(std::string keyTitle, std::string keyMessage){
    std::ifstream cfg("resources/config.ini");
    std::string title = "[" + keyTitle + "]";
    std::string message = keyMessage + "=";
    std::string line;
    bool hasKey = false;
    while(std::getline (cfg, line)){
        if(line[0] == '#' || line.empty()) {
            continue;
        }
        if(line[0] == '['){
            hasKey = (line == title);
        } else if(hasKey && line.rfind(message, 0) == 0){
            return line.substr(message.length());
        }
    }
    return "";
}

int Config::parseInt(std::string keyTitle, std::string keyMessage){
    int i = 0;
    try {
        i = std::stoi(parse(keyTitle, keyMessage));
    } catch(...){
        logger.print(logger.ERROR, "Cant convert string to integer from config file");
    }

    return i;
}

float Config::parseFloat(std::string keyTitle, std::string keyMessage){
    float f = 0;
    try {
        f = std::stof(parse(keyTitle, keyMessage));
    } catch (...){
        logger.print(logger.ERROR, "Cant convert string to float from config file");
    }
    return f;
}
