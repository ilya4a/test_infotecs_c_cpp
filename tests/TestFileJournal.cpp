#include <cassert>
#include <filesystem>
#include <fstream>
#include <string>

#include "FileJournal.h"

void test_file_is_created() {
    const std::filesystem::path path = std::filesystem::temp_directory_path() / "file_journal_test.txt";

    std::filesystem::remove(path);

    {
        FileJournal journal(path);

        assert(std::filesystem::exists(path));
        assert(std::filesystem::is_regular_file(path));
    }

    std::filesystem::remove(path);
}

void test_parent_directories_are_created() {
    const std::filesystem::path path =
        std::filesystem::temp_directory_path() / "file_journal_test" / "dir1" / "dir2" / "journal.txt";

    const std::filesystem::path root = std::filesystem::temp_directory_path() / "file_journal_test";

    std::filesystem::remove_all(root);

    {
        FileJournal journal(path);
        assert(std::filesystem::exists(path));
        assert(std::filesystem::is_regular_file(path));
        assert(std::filesystem::exists(root / "dir1"));
        assert(std::filesystem::exists(root / "dir1" / "dir2"));
    }

    std::filesystem::remove_all(root);
}

void test_write_respects_log_level() {
    const std::filesystem::path path = std::filesystem::temp_directory_path() / "file_journal_level.txt";

    std::filesystem::remove(path);

    {
        FileJournal journal(path, LogLevel::medium);

        Message low_message { "low message", LogLevel::low

        };

        Message medium_message { "medium message", LogLevel::medium };

        Message high_message { "high message", LogLevel::high };

        journal.write(low_message);
        journal.write(medium_message);
        journal.write(high_message);
    }

    std::ifstream file(path);

    assert(file.is_open());

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    assert(content.find("low message") == std::string::npos);
    assert(content.find("medium message") != std::string::npos);
    assert(content.find("high message") != std::string::npos);

    std::filesystem::remove(path);
}

int testFileJournal() {
    test_file_is_created();
    test_parent_directories_are_created();
    test_write_respects_log_level();

    return 0;
}

