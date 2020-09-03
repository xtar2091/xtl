#pragma once

#include <atomic>
#include <condition_variable>
#include <future>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>
#include <queue>

namespace xtl {

class ThreadPool {
private:
    class AsyncTaskCallable {
    private:
        struct CallableBase {
            virtual void call() = 0;
            virtual ~CallableBase() {}
        };

        template <class FunctionType>
        struct CallableImpl : CallableBase {
            FunctionType func_;
            CallableImpl(FunctionType&& func)
                : func_(std::move(func))
            {}
            virtual void call() {
                func_();
            }
        };

        std::unique_ptr<CallableBase> impl_;

    public:
        AsyncTaskCallable();

        template <class FunctionType>
        AsyncTaskCallable(FunctionType&& f)
            : impl_(new CallableImpl<FunctionType>(std::move(f))) {

        }

        AsyncTaskCallable(AsyncTaskCallable&& other);
        AsyncTaskCallable& operator=(AsyncTaskCallable&& other);
        AsyncTaskCallable(const AsyncTaskCallable&) = delete;
        AsyncTaskCallable(AsyncTaskCallable&) = delete;
        AsyncTaskCallable& operator=(const AsyncTaskCallable&) = delete;

        void operator()();
    };

public:
    bool Start(int pool_size);
    void Stop();

    template <class FunctionType>
    std::future<typename std::result_of<FunctionType()>::type> Append(FunctionType&& func) {
        using result_type = typename std::result_of<FunctionType()>::type;
        std::packaged_task<result_type()> task(std::move(func));
        std::future<result_type> future = task.get_future();
        std::lock_guard<std::mutex> lk(mtx_);
        tasks_.push(AsyncTaskCallable(std::move(task)));
        cv_.notify_one();
        return future;
    }

private:
    void WorkThread();

private:
    std::mutex mtx_;
    std::condition_variable cv_;
    std::vector<std::thread> pool_;
    std::queue<AsyncTaskCallable> tasks_;
    std::atomic<bool> next_;
};

}
