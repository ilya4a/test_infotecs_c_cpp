
#include "App.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>

#include "ThreadSafeQueue.h"

void App::writer_func() {
    try {
        while (auto command = queue.pop()) {
            if (command->type == Command::CommandType::Write) {
                journal->write(command->message);
            }else if (command->type == Command::CommandType::ChangeLevel) {
                LogLevel level = command->message.message_level;
                journal->set_default_level(level);
                journal->write_forced(ChangeLevel_command_message + LogLevel_to_string(level));
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
    LogLevel log_level;

    while (!queue.closed()) {
        try {
            pair = read_pair_input();
            std::cout << "first: " << pair.first << std::endl;
            std::cout << "second: " << pair.second << std::endl;
            log_level = LogLevel_from_string(pair.second);
        }catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            continue;
        }
        
        Message message(pair.first, log_level);

        if (pair.first.empty()) {
            if (!pair.second.empty()) {
                Command command(message, Command::CommandType::ChangeLevel);
                queue.push(command);
            }else {
                std::cerr << "Error: message is empty" << std::endl;
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
    std::string text, option;
    std::string line;

    if (!std::getline(std::cin, line)) {
        throw std::runtime_error("invalid args");
    }

    std::size_t open_quote = line.find('"');

    if (open_quote != std::string::npos) {

        for (size_t i = 0; i < open_quote; i++) {
            if (!std::isspace(line[i])) throw std::runtime_error("invalid args");
        }

        std::size_t close_quote = line.find('"', open_quote + 1);

        if (close_quote == std::string::npos) throw std::runtime_error("missing closing quote");

        text = line.substr( open_quote + 1, close_quote - open_quote - 1);

        std::size_t option_pos = line.find('-', close_quote + 1);

        if (option_pos != std::string::npos) {
            for (size_t i = close_quote + 1; i < option_pos; i++) {
                if (!std::isspace(line[i])) throw std::runtime_error("invalid args");
            }
            option = line.substr(option_pos + 1);

        }else{
            for (size_t i = close_quote + 1; i < line.size(); i++) {
                if (!std::isspace(line[i])) throw std::runtime_error("invalid args");
            }
        }

    }else {
        std::size_t option_pos = line.find('-');

        if (option_pos != std::string::npos) {
            for (size_t i = 0; i < option_pos; i++) {
                if (!std::isspace(line[i]))
                    throw std::runtime_error("invalid args");
            }

            option = line.substr(option_pos + 1);
        }else {
            for (size_t i = 0; i < line.size(); i++) {
                if (!std::isspace(line[i])) throw std::runtime_error("invalid args");
            }
        }
    }

    return {text, option};
}


App::~App() {
    queue.close();
    writer.join();
}
