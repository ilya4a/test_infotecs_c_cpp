
#ifndef C_CPP_ASSIGNMENT_LOGLEVEL_H
#define C_CPP_ASSIGNMENT_LOGLEVEL_H

#include <stdexcept>

enum class LogLevel {
    low = 0,
    medium = 1,
    high= 2
};

inline std::string LogLevel_to_string(LogLevel level) {
    switch (level) {
        case LogLevel::low: return "low";
        case LogLevel::medium: return "medium";
        case LogLevel::high: return "high";
    }

    throw std::invalid_argument("unknown string to log level");
}


inline LogLevel LogLevel_from_string(const std::string& str) {
    if (str == "-low") return LogLevel::low;
    if (str == "l") return LogLevel::low;
    if (str == "-medium") return LogLevel::medium;
    if (str == "m") return LogLevel::medium;
    if (str == "-high") return LogLevel::high;
    if (str == "h") return LogLevel::high;

    if (str == "") return LogLevel::low;

    throw std::invalid_argument("unknown log level");
}


#endif // C_CPP_ASSIGNMENT_LOGLEVEL_H
