#include "Config.h"
#include <iostream>
#include <fstream>

Config::Config(){

}

void Config::init(){
    std::ifstream file("resources/config.ini");
    if(file.is_open()) return;

    std::ofstream cfg("resources/config.ini");
    cfg << "[game_info]\n";
    cfg << "name=\n";
    cfg << "version=\n";
    cfg << "width=\n";
    cfg << "height=\n";
    Logger::print(Logger::INFO, "Config file has been successfully created");
}

std::string Config::findSpecial(std::string content){
    if(content[0] != '$'){
        Logger::print(Logger::ERROR, "Failed to find special in content without special symbol");
        return "";
    }
    content.erase(0, 1);
    size_t pos = content.find("|");
    if(pos != std::string::npos){
        std::string key = content.substr(0, pos);
        std::string value = content.substr(pos + 1);
        return parse<std::string>(key, value);
    }
    return parse<std::string>("game_info", content);
}