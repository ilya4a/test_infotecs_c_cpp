
#ifndef C_CPP_ASSIGNMENT_APP_H
#define C_CPP_ASSIGNMENT_APP_H
#include <memory>
#include <thread>

#include "IJournal.h"
#include "ThreadSafeQueue.h"

class App {
    std::unique_ptr<IJournal> journal;
    std::thread writer;
    ThreadSafeQueue queue;

    std::exception_ptr writer_exception;

    void writer_func();

    void handle_message(Message message);


public:

    App(std::unique_ptr<IJournal> journal);

    void run();

    static std::pair<std::string, std::string> read_pair_input();
    ~App();

};


#endif // C_CPP_ASSIGNMENT_APP_H
