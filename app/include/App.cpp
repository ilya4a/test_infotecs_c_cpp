
#include "App.h"

#include <iostream>

#include "ThreadSafeQueue.h"

void App::writer_func() {

    try {
        while (auto message = queue.pop()) {
            journal->write(*message);
        }
    }catch (...) {
        writer_exception = std::current_exception();
        queue.close();
    }
}

void App::handle_message(Message message) {
    queue.push(std::move(message));
}

void App::run() {
    std::string line;
    while (1) {

        std::getline(std::cin, line);

        if (writer_exception) {
            std::rethrow_exception(writer_exception);
        }

        handle_message(Message(line, LogLevel::low));
    }
}


App::~App() {
    queue.close();
    writer.join();
}
