
#ifndef C_CPP_ASSIGNMENT_APP_H
#define C_CPP_ASSIGNMENT_APP_H
#include <memory>
#include <thread>

#include "IJournal.h"
#include "ThreadSafeQueue.h"


struct Command {
    enum class CommandType {
        Write,
        ChangeLevel
    };

    Message message;
    CommandType type;

    Command(Message message, CommandType type) :message(std::move(message)), type(type){};

};

class App {
    std::unique_ptr<IJournal> journal;
    std::thread writer;
    ThreadSafeQueue<Command> queue;

    std::exception_ptr writer_exception;

    void writer_func();

public:
    App(std::unique_ptr<IJournal> journal);

    void run();
    static std::pair<std::string, std::string> read_pair_input();

    App(const App&) = delete;
    App& operator=(const App&) = delete;
    App(App&&) = delete;
    App& operator=(App&&) = delete;

    ~App();

};


#endif // C_CPP_ASSIGNMENT_APP_H
