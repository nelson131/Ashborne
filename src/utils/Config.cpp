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
