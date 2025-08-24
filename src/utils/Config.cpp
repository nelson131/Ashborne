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