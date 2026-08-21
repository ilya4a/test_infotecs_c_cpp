#include <iostream>

#include "App.h"
#include "FileJournal.h"
#include <utility>
#include <string>




int main() {
    try {

        std::cout << "Enter filename and default log level (press Enter to use default):\n";
        std::cout << "Usage: --help" << std::endl;

        std::pair<std::string, std::string> input = App::read_pair_input();

        while (input.second == "-help" ) {
            std::cout << help << std::endl;
            std::cout << "Enter filename and default log level (press Enter to use default):\n";
            std::cout << "Usage: --help" << std::endl;
            input = App::read_pair_input();
        }

        LogLevel level = LogLevel_from_string(input.second);

        std::unique_ptr<FileJournal> fj = std::make_unique<FileJournal>(input.first, level );
        fj->write_forced("JOURNAL. log level: " + LogLevel_to_string(level));
        std::cout << "Journal created" << std::endl;

        App app(std::move(fj));
        app.run();

    }catch (const std::exception& e) {
        std::cerr <<e.what()<< std::endl;
        return 1;
    }

    return 0;
}
