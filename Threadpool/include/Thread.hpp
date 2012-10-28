#ifndef RAHU_THREAD_HPP_INC
#define RAHU_THREAD_HPP_INC

#include <thread>

namespace rahu
{
  class Thread
  {
    public:
      Thread();
      virtual ~Thread();

      void start();
      void join();
    protected:
      virtual void run() = 0;

    private:
      Thread(Thread&) = delete;
      void operator=(Thread&) = delete;
      std::thread m_thread;
  };
}

#endif
