#include <iostream>

#include "App.h"
#include "FileJournal.h"

int main() {

    // FileJournal fg("dir/file_journal.txt");
    // fg.write("text1", LogLevel::low);
    //
    // fg.set_default_level(LogLevel::high);
    //
    // fg.write("text2", LogLevel::low);
    // std::cout << "Hello, World!" << std::endl;
    //

    std::unique_ptr<FileJournal> fj = std::make_unique<FileJournal>("");
    App app(std::move(fj));
    app.handle_message("some new MAAAAsage");
    return 0;
}
