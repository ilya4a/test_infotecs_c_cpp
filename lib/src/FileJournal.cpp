
#include "FileJournal.h"

#include <fstream>

constexpr const char* DefaultLogName = "journal_";
constexpr const char* DefaultLogExt = ".txt";


static std::string generate_filename() {
    auto now = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    return std::string(DefaultLogName)  + std::to_string(ms) + std::string(DefaultLogExt);
}


FileJournal::FileJournal(std::filesystem::path file_path, LogLevel level) : journal_level(level){

    if (std::filesystem::is_directory(file_path)) {
        throw std::runtime_error("Journal file is directory");
    }

    if (file_path.empty()) {
        file_path = std::filesystem::current_path();
        file_path /= generate_filename();
    }

    std::filesystem::create_directories(file_path.parent_path());

    journal.open(file_path, std::ios::app);

    if (!journal.is_open()) {
        throw std::runtime_error("Can't open journal file");
    }

}

std::string current_time_str() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
    localtime_r(&t, &tm);
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm);
    return buf;
}

void FileJournal::write(const std::string &message, LogLevel message_level) {
    if (message_level < journal_level) return;
    journal << '\n' << current_time_str() << ' ' << to_string(message_level) << ' ' << message;
}

void FileJournal::set_default_level(LogLevel level) {
    journal_level = level;
}
