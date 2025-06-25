#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include "Logger.h"

class Config {
    
    public:
    Config();
    void config_init();

    std::string config_parse(std::string key_title, std::string key_message);
    int config_parseInt(std::string key_title, std::string key_message);

    private:
    Logger logger;
};

#endif