#include "Command.h"
Command::Command(Message message, CommandType type) : message(std::move(message)), type(type) { };
