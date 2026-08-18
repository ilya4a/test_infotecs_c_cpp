
#ifndef C_CPP_ASSIGNMENT_LOGLEVEL_H
#define C_CPP_ASSIGNMENT_LOGLEVEL_H

enum class LogLevel {
    low = 0,
    medium = 1,
    high= 2
};

inline std::string to_string(LogLevel level) {
    switch (level) {
        case LogLevel::low: return "low";
        case LogLevel::medium: return "medium";
        case LogLevel::high: return "high";
    }
    return "unknown";
}


#endif // C_CPP_ASSIGNMENT_LOGLEVEL_H
