#include "config.hpp"

#include <iostream>

#include "error_handler.hpp"

Config config;

Config::Config() {
    file = std::ifstream("resources/config.ini");
    if (!file.is_open()) {
        raise_error(ERR_FILE_NOT_FOUND, "config.ini");
    }
}
