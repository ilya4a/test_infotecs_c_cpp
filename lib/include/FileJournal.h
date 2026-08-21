
#ifndef C_CPP_ASSIGNMENT_FILEJOURNAL_H
#define C_CPP_ASSIGNMENT_FILEJOURNAL_H

#include <filesystem>
#include <fstream>

#include "IJournal.h"


class FileJournal : public IJournal {
    std::ofstream journal;
    LogLevel journal_level;

public:

    FileJournal(std::filesystem::path file_path, LogLevel level = LogLevel::low);

    ~FileJournal() override = default;

    void write(const Message& message) override;
    void write_forced(std::string message_text) override;
    void set_default_level(LogLevel level) override;
};


#endif // C_CPP_ASSIGNMENT_FILEJOURNAL_H
