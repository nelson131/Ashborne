#include <iostream>
#include <fstream>
#include "Config.h"

Config::Config(){

}

void Config::config_init(){
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

std::string Config::config_parse(std::string key_title, std::string key_message){
    std::ifstream cfg("resources/config.ini");
    std::string title = "[" + key_title + "]";
    std::string message = key_message + "=";
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

int Config::config_parseInt(std::string key_title, std::string key_message){
    int i = 0;
    try {
        i = std::stoi(config_parse(key_title, key_message));
    } catch(...){
        logger.print(logger.ERROR, "Cant convert string to integer from config file");
    }

    return i;
}

float Config::config_parseFloat(std::string key_title, std::string key_message){
    float f = 0;
    try {
        f = std::stof(config_parse(key_title, key_message));
    } catch (...){
        logger.print(logger.ERROR, "Cant convert string to float from config file");
    }
    return f;
}
