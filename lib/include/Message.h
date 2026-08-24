#ifndef C_CPP_ASSIGNMENT_MESSAGE_H
#define C_CPP_ASSIGNMENT_MESSAGE_H

#include "LogLevel.h"
#include <string>

struct Message {
    const std::string message_text;
    const LogLevel message_level;

    Message(std::string message, LogLevel message_level);
};

#endif // C_CPP_ASSIGNMENT_MESSAGE_H
