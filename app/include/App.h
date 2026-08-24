
#ifndef C_CPP_ASSIGNMENT_APP_H
#define C_CPP_ASSIGNMENT_APP_H

#include <memory>
#include <thread>

#include "Command.h"
#include "IJournal.h"
#include "ThreadSafeQueue.h"


class App {
    std::unique_ptr<IJournal> journal;
    std::thread writer;
    ThreadSafeQueue<Command> queue;

    std::exception_ptr writer_exception;

    static inline std::string ChangeLevel_command_message = "journal level changed: ";

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

const std::string help = R"(Usage:
  <file> <log level>
  <message> <log level>
-q to exit

Log levels:
  -l    low
  -m    medium
  -h    high

Startup:
  "path/to/file" -l/-m/-h

  File path can be omitted. In this case, the log file
  is created automatically in the current directory.

  Log level can be omitted. In this case, the default level is low.

Messages:
  "message" -l/-m/-h

  Log level can be omitted. In this case, the message uses
  the LOW level.

Change default journal level:
  -l
  -m
  -h

The file log level is the minimum level of messages written to the log.
)";


#endif // C_CPP_ASSIGNMENT_APP_H
