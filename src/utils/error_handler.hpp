#pragma once

#include <sstream>
#include <vector>

#include "log.hpp"

enum Error {
    // General
    FAILED,
    NONE,
    OK,
    ERR_NEGATIVE_NUM,
    ERR_NULLPTR_OBJECT,
    ERR_FILE_NOT_FOUND
};

extern std::vector<const char*> error_messages;

template <typename... targs>
void raise_error(Error error, const targs&... args) {
    if (error >= error_messages.size()) {
        clog(ERR, "Failed to raise the error: ", error);
    } else {
        std::stringstream str;
        (str << ... << args);
        clog(ERR, " -> ", error, ": ", error_messages[error], ".\n", str.str());
    }
}
