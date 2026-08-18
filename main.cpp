#include <iostream>

#include "FileJournal.h"

int main() {

    FileJournal fg("dir/file_journal.txt");
    fg.write("text1", LogLevel::low);

    fg.set_default_level(LogLevel::high);

    fg.write("text2", LogLevel::low);
    std::cout << "Hello, World!" << std::endl;

    return 0;
}
