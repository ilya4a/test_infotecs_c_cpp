#include "Message.h"
Message::Message(std::string message, LogLevel message_level)
    : message_text(std::move(message)),
      message_level(message_level) { };
