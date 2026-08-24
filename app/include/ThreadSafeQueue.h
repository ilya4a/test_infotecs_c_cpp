
#ifndef C_CPP_ASSIGNMENT_THREADSAFEQUEUE_H
#define C_CPP_ASSIGNMENT_THREADSAFEQUEUE_H
#include <condition_variable>
#include <mutex>
#include <optional>
#include <queue>

#include "Message.h"

template<typename T>
class ThreadSafeQueue {

    std::queue<T> queue;

    std::mutex mutex;
    std::condition_variable cv;
    bool is_closed = false;

public:

    bool closed() {
        return is_closed;
    }

    void push(T data) {

        std::unique_lock<std::mutex> lock(mutex);
        if (is_closed) throw std::runtime_error("Queue is closed");;
        queue.push(std::move(data));
        lock.unlock();

        cv.notify_one();
    }

    std::optional<T> pop() {
        std::unique_lock<std::mutex> lock(mutex);

        cv.wait(lock, [this] {return !queue.empty() || is_closed;});
        if (queue.empty()) {
            return std::nullopt;
        }

        T message = std::move(queue.front());
        queue.pop();

        return message;
    }

    void close() {

        std::unique_lock<std::mutex> lock(mutex);
        is_closed = true;
        lock.unlock();

        cv.notify_all();
    }
};



#endif // C_CPP_ASSIGNMENT_THREADSAFEQUEUE_H
