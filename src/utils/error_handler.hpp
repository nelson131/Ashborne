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
    ERR_SOMETHING_NOT_FOUND,
    ERR_FILE_NOT_FOUND,
    // Config
    ERR_FAILED_CONVERT,
    ERR_KEY_NOT_FOUND,
    // Texture
    ERR_FAILED_LOAD_SURFACE,
    ERR_FAILED_LOAD_TEXTURE,
    ERR_TEXTURE_IS_NULLPTR,
    // Vector
    ERR_DIVIDE_ON_ZERO,
    ERR_NULL_VECTOR
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
