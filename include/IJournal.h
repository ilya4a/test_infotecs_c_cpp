#ifndef C_CPP_ASSIGNMENT_IJOURNAL_H
#define C_CPP_ASSIGNMENT_IJOURNAL_H
#include <string>

#include "LogLevel.h"

class IJournal {
    virtual ~IJournal() = default;

    virtual void write(const std::string& message,
                      LogLevel level) = 0;

    virtual void set_default_level(LogLevel level);
};

#endif // C_CPP_ASSIGNMENT_IJOURNAL_H
