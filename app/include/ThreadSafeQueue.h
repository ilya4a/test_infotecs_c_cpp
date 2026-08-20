
#ifndef C_CPP_ASSIGNMENT_THREADSAFEQUEUE_H
#define C_CPP_ASSIGNMENT_THREADSAFEQUEUE_H
#include <condition_variable>
#include <mutex>
#include <optional>
#include <queue>
#include "Message.h"

class ThreadSafeQueue {

    std::queue<Message> queue;

    std::mutex mutex;
    std::condition_variable cv;
    bool is_closed = false;

public:
    void push(Message message);

    std::optional<Message> pop();
    void close();

};


#endif // C_CPP_ASSIGNMENT_THREADSAFEQUEUE_H
