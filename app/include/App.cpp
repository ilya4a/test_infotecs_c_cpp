
#include "App.h"

#include <iostream>
#include <sstream>

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
    std::pair<std::string, std::string> pair;
    while (1) {

        std::getline(std::cin, line);
        pair = read_pair_input();
        if (writer_exception) {
            std::rethrow_exception(writer_exception);
        }

        handle_message(Message(pair.first, from_string(pair.second)));
    }
}

std::pair<std::string, std::string> App::read_pair_input() {
    std::string text, option, rest;
    char ch;
    while (std::cin.get(ch) && ch != '"');
    if (!std::cin) throw std::runtime_error("invalid args");
    while (std::cin.get(ch) && ch != '"') text += ch;
    if (!std::cin) throw std::runtime_error("invalid args");
    std::getline(std::cin, rest);
    std::istringstream iss(rest);
    iss >> option;
    return {text, option};
}

App::~App() {
    queue.close();
    writer.join();
}
