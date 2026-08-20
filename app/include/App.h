
#ifndef C_CPP_ASSIGNMENT_APP_H
#define C_CPP_ASSIGNMENT_APP_H
#include <memory>

#include "IJournal.h"

class App {
    std::unique_ptr<IJournal> journal;


public:

    App(std::unique_ptr<IJournal> journal) : journal(std::move(journal)) {

    }

    void handle_message(std::string&& str);

};


#endif // C_CPP_ASSIGNMENT_APP_H
