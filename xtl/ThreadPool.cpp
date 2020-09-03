#include "xtl/ThreadPool.h"
#include <cstdio>
namespace xtl {

ThreadPool::AsyncTaskCallable::AsyncTaskCallable() {

}

ThreadPool::AsyncTaskCallable::AsyncTaskCallable(AsyncTaskCallable&& other)
    : impl_(std::move(other.impl_)) {
}

ThreadPool::AsyncTaskCallable& ThreadPool::AsyncTaskCallable::operator=(ThreadPool::AsyncTaskCallable&& other) {
    impl_ = std::move(other.impl_);
    return *this;
}

void ThreadPool::AsyncTaskCallable::operator()() {
    if (impl_) {
        impl_->call();
    }
}

bool ThreadPool::Start(int pool_size) {
    unsigned int ps = std::thread::hardware_concurrency();
    if (pool_size > 0) {
        ps = static_cast<unsigned int>(pool_size);
    }
    next_ = true;
    for (unsigned int i = 0; i < ps; i++) {
        pool_.push_back(std::thread(&ThreadPool::WorkThread, this));
    }
    return true;
}

void ThreadPool::Stop() {
    next_ = false;
    {
        std::unique_lock<std::mutex> lk(mtx_);
        cv_.notify_all();
    }
    for (auto& thrd : pool_) {
        if (thrd.joinable()) {
            thrd.join();
        }
    }
}

void ThreadPool::WorkThread() {
    while (next_) {
        AsyncTaskCallable task;
        {
            std::unique_lock<std::mutex> lk(mtx_);
            cv_.wait(lk, [this]() -> bool {
                return !this->tasks_.empty() || !next_;
            });
            if (!tasks_.empty()) {
                task = std::move(tasks_.front());
                tasks_.pop();
            }
        }
        if (next_) {
            task();
        }
    }
}

}

