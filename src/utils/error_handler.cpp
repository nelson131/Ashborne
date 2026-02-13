#include "error_handler.hpp"

#include <iostream>

std::vector<const char*> error_messages{
    "Failed",
    "None",
    "OK",
    "Number cant be negative",
    "Nullptr object",
    "Failed to find the file",
    "Failed to convert string in the config parser",
    "Failed to find info in the config",
    "Failed to load the surface",
    "Failed to load the texture",
    "Texture like an argument is nullptr object",
    "Failed to operate divide cause v.x or v.y is zero",
    "Failed to operate vector cause vector is null"};
