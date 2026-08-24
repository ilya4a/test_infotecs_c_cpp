

#include <iostream>
#include <cassert>
#include <chrono>
#include <thread>
#include <stdexcept>


#include "ThreadSafeQueue.h"

void test_close_empty_queue() {
    ThreadSafeQueue<int> queue;
    queue.close();
    auto result = queue.pop();
    assert(!result.has_value());
}

void test_push_after_close() {
    ThreadSafeQueue<int> queue;

    queue.close();

    bool exception_thrown = false;

    try {
        queue.push(42);
    } catch (const std::runtime_error&) {
        exception_thrown = true;
    }

    assert(exception_thrown);
}

void test_close_preserves_queued_messages() {
    ThreadSafeQueue<int> queue;

    queue.push(10);
    queue.push(20);

    queue.close();

    auto first = queue.pop();
    auto second = queue.pop();
    auto third = queue.pop();

    assert(first.has_value());
    assert(second.has_value());
    assert(!third.has_value());

    assert(first.value() == 10);
    assert(second.value() == 20);
}

void test_push_unblocks_blocking_pop() {
    ThreadSafeQueue<int> queue;
    const int N = 10;

    std::vector<std::optional<int>> results;

    std::thread consumer([&]() {
        for (int i = 0; i < N; i++) {
            results.push_back(queue.pop());
        }
    });
    for (int i = 0; i < N; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        queue.push(i);
    }

    consumer.join();

    for (int i = 0; i < N; i++) {
        assert(results[i].has_value());
        assert(results[i].value() == i);
    }
}

int testThreadSafeQueue() {
    test_close_empty_queue();
    test_push_after_close();
    test_close_preserves_queued_messages();
    test_push_unblocks_blocking_pop();

    return 0;
}