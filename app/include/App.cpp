
#include "App.h"


void App::handle_message(std::string &&str) {
    journal->write(str, LogLevel::low);
}
