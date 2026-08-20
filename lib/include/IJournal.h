#ifndef C_CPP_ASSIGNMENT_IJOURNAL_H
#define C_CPP_ASSIGNMENT_IJOURNAL_H
#include <string>

#include "LogLevel.h"
#include "Message.h"

class IJournal {
public:
    virtual ~IJournal() = default;

    virtual void write(const Message& message) = 0;

    virtual void set_default_level(LogLevel level) = 0;
};

#endif // C_CPP_ASSIGNMENT_IJOURNAL_H
