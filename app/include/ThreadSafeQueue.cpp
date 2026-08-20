
#include "ThreadSafeQueue.h"

#include <stdexcept>


void ThreadSafeQueue::push(Message message) {

    std::unique_lock<std::mutex> lock(mutex);
    if (is_closed) throw std::runtime_error("Queue is closed");;
    queue.push(std::move(message));
    lock.unlock();

    cv.notify_one();
}


std::optional<Message> ThreadSafeQueue::pop() {
    std::unique_lock<std::mutex> lock(mutex);

    cv.wait(lock, [this] {return !queue.empty() || is_closed;});
    if (queue.empty()) {
        return std::nullopt;
    }

    Message message = std::move(queue.front());
    queue.pop();

    return message;
}


void ThreadSafeQueue::close() {

    std::unique_lock<std::mutex> lock(mutex);
    is_closed = true;
    lock.unlock();

    cv.notify_all();
}

