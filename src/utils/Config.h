#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include "Logger.h"

class Config {
    
    public:
    Config();
    void init();

    std::string parse(std::string keyTitle, std::string keyMessage);
    int parseInt(std::string keyTitle, std::string keyMessage);
    float parseFloat(std::string keyTitle, std::string keyMessage);

    private:
    Logger logger;
};

#endif