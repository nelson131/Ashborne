#pragma once

#include <iostream>
#include <sstream>
#include <string>

#define RED "\033[31m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define PURPLE "\033[35m"
#define RESET "\033[0m"

#define INFO_PREFIX BLUE "[INFO] " RESET;
#define ERROR_PREFIX RED "[ERROR] " RESET;
#define DEBUG_PREFIX PURPLE "[DEBUG] " RESET;
#define WARNING_PREFIX YELLOW "[WARNING] " RESET;
#define SUCCESS_PREFIX GREEN "[SUCCESS] " RESET;

enum LogType { INFO, ERR, DEBUG, WARNING, SUCCESS };

const char* get_prefix(LogType type);

template <typename... targs>
void clog(LogType log_type, const targs&... args) {
    std::ostringstream str;
    (str << ... << args);
    std::cout << get_prefix(log_type) << str.str() << std::endl;
}
