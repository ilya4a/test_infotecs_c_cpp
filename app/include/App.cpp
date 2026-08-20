
#include "App.h"
#include "ThreadSafeQueue.h"

void App::writer_func() {
    while (auto message = queue.pop()) {
        journal->write(message.value());
    }
}

void App::handle_message(Message message) {
    queue.push(std::move(message));
}

App::~App() {
    queue.close();
    writer.join();
}
