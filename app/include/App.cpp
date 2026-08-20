
#include "App.h"

#include <iostream>
#include <sstream>

#include "ThreadSafeQueue.h"

void App::writer_func() {
    try {
        while (auto command = queue.pop()) {
            if (command->type == Command::CommandType::Write) {
                journal->write(command->message);
            }else if (command->type == Command::CommandType::ChangeLevel) {
                journal->set_default_level(command->message.message_level);
            }else {
                throw std::runtime_error("Unknown type of command");
            }
        }
    }catch (...) {
        writer_exception = std::current_exception();
        queue.close();
    }
}


App::App(std::unique_ptr<IJournal> journal)  : journal(std::move(journal)){
    writer = std::thread([this]{writer_func();});
}

void App::run() {
    std::string line;
    std::pair<std::string, std::string> pair;


    while (!queue.closed()) {

        pair = read_pair_input();
        std::cout << "first: " << pair.first << std::endl;
        std::cout << "second: " << pair.second << std::endl;

        Message message(pair.first, LogLevel_from_string(pair.second));

        if (pair.first.empty()) {
            if (!pair.second.empty()) {
                Command command(message, Command::CommandType::ChangeLevel);
                queue.push(command);
            }
        }else {
            Command command(message, Command::CommandType::Write);
            queue.push(command);
        }

        if (writer_exception) {
            std::rethrow_exception(writer_exception);
        }

    }
}

std::pair<std::string, std::string> App::read_pair_input() {
    std::string text, option, rest;
    char ch = ' ';
    while (std::cin.get(ch) && ch != '\n' && ch != '"' && ch != '-'){}

    if (ch == '\n') return {text, option};

    if (ch == '"') {
        if (!std::cin) throw std::runtime_error("invalid args");
        while (std::cin.get(ch) && ch != '"') text += ch;
        if (!std::cin) throw std::runtime_error("invalid args");
    }else {
        option += ch;
    }

    std::getline(std::cin, rest);
    std::istringstream iss(rest);

    std::string temp = option;
    iss >> option;
    return {text, temp + option};
}

App::~App() {
    queue.close();
    writer.join();
}
