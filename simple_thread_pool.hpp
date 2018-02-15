#pragma once

#include <future>
#include <list>
#include <vector>

namespace sandbox {

template <typename R>
class simple_thread_pool
{
public:
    explicit simple_thread_pool(size_t num_threads = std::thread::hardware_concurrency())
        : finished{false}
    {
        threads.reserve(num_threads);
        for (size_t i = 0; i < num_threads; ++i)
        {
            threads.emplace_back([this] { do_work(); });
        }
    }

    ~simple_thread_pool() { quit(); }

    template <typename T>
    std::future<R> add_task(T&& t)
    {
        std::future<R> fut;
        {
            std::lock_guard<std::mutex> lock{sync};
            tasks.emplace_back(t);
            fut = tasks.back().get_future();
        }
        cv.notify_one();
        return fut;
    }

    void quit()
    {
        finished = true;
        cv.notify_all();
        for (auto& t : threads)
            t.join();
    }

private:
    void do_work()
    {
        while (true)
        {

            std::list<task_t> task;

            {
                std::unique_lock<std::mutex> lock{sync};
                cv.wait(lock, [this] { return tasks.size() || finished; });
                if (tasks.size())
                    task.splice(task.end(), tasks, tasks.begin());
            }

            if (task.size())
            {
                task.front()();
            }
            else
            {
                return;
            }
        }
    }

    using task_t = std::packaged_task<R()>;

    std::atomic_bool finished;
    std::condition_variable cv;
    std::mutex sync;
    std::list<task_t> tasks;
    std::vector<std::thread> threads;
};
}
