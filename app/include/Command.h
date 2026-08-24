#ifndef C_CPP_ASSIGNMENT_COMMAND_H
#define C_CPP_ASSIGNMENT_COMMAND_H
#include "Message.h"

struct Command {
    enum class CommandType { Write, ChangeLevel };

    Message message;
    CommandType type;

    Command(Message message, CommandType type);
};

#endif // C_CPP_ASSIGNMENT_COMMAND_H
