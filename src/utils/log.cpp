#include "log.hpp"

const char* get_prefix(LogType log_type) {
    switch (log_type) {
        case INFO:
            return INFO_PREFIX;
        case ERR:
            return ERROR_PREFIX;
        case DEBUG:
            return DEBUG_PREFIX;
        case WARNING:
            return WARNING_PREFIX;
        case SUCCESS:
            return SUCCESS_PREFIX;
    }

    return INFO_PREFIX;
}
