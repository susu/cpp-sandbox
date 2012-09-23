#ifndef CONS_HPP_INC
#define CONS_HPP_INC

#include <sstream>

#include "Queue.hpp"
#include "Signaler.hpp"
#include "Exceptions.hpp"

template<class T>
class Consumer
{
  public:
    Consumer(int id, ConcQueue<T> & qu, Signaler const & s)
      : m_id(id)
      , m_sourceQueue(qu)
      , m_signaler(s)
    {}
    Consumer(Consumer&&) = default;
    void run()
    {
      try 
      {
        while( true )
        {
          T p = m_sourceQueue.waitAndPop();
          // processing
          std::stringstream ss;
          ss << "Consumer-" << m_id << " " << p;
          mutexedPrint( ss.str() );
        }
      }
      catch(FunIsOver & ex)
      {
        std::stringstream ss;
        ss << "Consumer-" << m_id << " EXIT";
        mutexedPrint( ss.str() );
      }
    }
  private:
    Consumer(Consumer&) = delete;
    void operator=(Consumer&) = delete;

    int m_id;
    ConcQueue<T> & m_sourceQueue;
    Signaler const & m_signaler;
};

#endif
