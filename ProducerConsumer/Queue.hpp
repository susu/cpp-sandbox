#ifndef Q_HPP_INC
#define Q_HPP_INC

#include <mutex>
#include <condition_variable>
#include <deque>
#include <iostream>

#include "Exceptions.hpp"
#include "Signaler.hpp"

template<class T>
class ConcQueue
{
  public:
    ConcQueue() 
      : m_signaler(m_condVar)
    {}
    void push(T const & thing)
    {
      std::unique_lock<std::mutex> lock(m_mutex);
      bool const empty( m_queue.empty() );
      m_queue.push_back( thing );
      lock.unlock();
      if (empty)
      {
        m_condVar.notify_one();
      }
    }
    T waitAndPop()
    {
      std::unique_lock<std::mutex> lock(m_mutex);
      while(m_queue.empty())
      {
        m_condVar.wait(lock);
        if( m_signaler.isSignaled(Signaler::SHUTDOWN))
        {
          throw FunIsOver();
        }
      }
      T out = m_queue.front();
      m_queue.pop_front();
      return out;
    }
    Signaler& getSignaler()
    {
      return m_signaler;
    }
  private:
    ConcQueue(ConcQueue&) = delete;
    void operator=(ConcQueue&) = delete;

    std::deque<T> m_queue;
    std::mutex    m_mutex;
    std::condition_variable m_condVar;

    Signaler m_signaler;
};

// TODO decent logger, not this ugly global
std::mutex g_printMutex;
void mutexedPrint( std::string const & msg )
{
  std::lock_guard<std::mutex> lock(g_printMutex);
  std::cout << msg << std::endl;
}

#endif
