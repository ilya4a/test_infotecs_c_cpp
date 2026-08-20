#include <iostream>

#include "App.h"
#include "FileJournal.h"
#include <utility>
#include <string>


#include <stdexcept>


int main() {

    std::pair<std::string, std::string> input = App::read_pair_input();

    std::cout << input.first << std::endl;
    std::cout << input.second << std::endl;

    std::unique_ptr<FileJournal> fj = std::make_unique<FileJournal>(input.first, from_string(input.second));

    App app(std::move(fj));
    app.run();
    return 0;
}
