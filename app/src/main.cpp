#include <iostream>

#include "App.h"
#include "FileJournal.h"
#include <utility>
#include <string>

int main() {

    try {
        std::pair<std::string, std::string> input = App::read_pair_input();

        // std::cout << "first: " << input.first << std::endl;
        // std::cout << "second: " << input.second << std::endl;
        LogLevel level = LogLevel_from_string(input.second);

        std::unique_ptr<FileJournal> fj = std::make_unique<FileJournal>(input.first, level );
        fj->write_forced("JOURNAL. log level: " + LogLevel_to_string(level));

        App app(std::move(fj));
        app.run();

    }catch (const std::exception& e) {
        std::cerr <<e.what()<< std::endl;
        return 1;
    }

    return 0;
}
