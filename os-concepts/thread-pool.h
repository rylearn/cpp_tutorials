#ifndef _thread_pool_
#define _thread_pool_

#include <cstddef>
#include <functional>
#include <thread>
#include <vector>
#include <queue>

class ThreadPool {
public:
  ThreadPool(size_t numThreads);
  void schedule(const std::function<void(void)>& thunk);
  void wait();
  ~ThreadPool();
private:
  std::thread dispatcher;
  std::vector<std::thread> worker_thread;
  int numScheduled = 0;
  std::queue<function<void(void)>> queue_of_functions;

  // remove copy and assignment constructors
  ThreadPool(const ThreadPool& original) = delete;
  ThreadPool& operator=(const ThreadPool& rhs) = delete;
};
#endif