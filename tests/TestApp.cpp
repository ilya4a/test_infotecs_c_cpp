#include <cassert>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "App.h"

struct TestJournalData {
    std::vector<Message> written_messages;
    std::vector<std::string> forced_messages;
    LogLevel current_level = LogLevel::low;
};

class TestJournal : public IJournal {
  public:
    std::shared_ptr<TestJournalData> data;

    TestJournal() : data(std::make_shared<TestJournalData>()) { }

    void write(const Message &message) override { data->written_messages.push_back(message); }

    void write_forced(std::string message_text) override { data->forced_messages.push_back(std::move(message_text)); }

    void set_default_level(LogLevel level) override { data->current_level = level; }
};

class CinRedirect {
    std::istringstream stream;
    std::streambuf *old_buffer;

  public:
    explicit CinRedirect(const std::string &input) : stream(input), old_buffer(std::cin.rdbuf(stream.rdbuf())) { }

    ~CinRedirect() { std::cin.rdbuf(old_buffer); }
};

void test_app_sends_message() {
    auto journal = std::make_unique<TestJournal>();
    std::shared_ptr<TestJournalData> data = journal->data;

    {
        CinRedirect input("\"hello world\" -h\n-q\n");

        App app(std::move(journal));
        app.run();
    }

    assert(data->written_messages.size() == 1);
    assert(data->written_messages[0].message_text == "hello world");
    assert(data->written_messages[0].message_level == LogLevel::high);
}

void test_app_changes_log_level() {
    auto journal = std::make_unique<TestJournal>();
    std::shared_ptr<TestJournalData> data = journal->data;

    {
        CinRedirect input("-m\n-q\n");

        App app(std::move(journal));
        app.run();
    }

    assert(data->current_level == LogLevel::medium);
    assert(data->forced_messages.size() == 1);
    assert(data->forced_messages[0] == "journal level changed: medium");
}

void test_parser_quoted_message_with_level() {
    CinRedirect input("\"hello world\" -h\n");

    auto result = App::read_pair_input();

    assert(result.first == "hello world");
    assert(result.second == "h");
}

void test_parser_quoted_message_without_level() {
    CinRedirect input("\"hello world\"\n");

    auto result = App::read_pair_input();

    assert(result.first == "hello world");
    assert(result.second.empty());
}

void test_parser_level_only() {
    CinRedirect input("-m\n");

    auto result = App::read_pair_input();

    assert(result.first.empty());
    assert(result.second == "m");
}

int testApp() {
    test_app_sends_message();
    test_app_changes_log_level();

    test_parser_quoted_message_with_level();
    test_parser_quoted_message_without_level();
    test_parser_level_only();

    return 0;
}
