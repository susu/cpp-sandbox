#ifndef PROD_HPP_INC
#define PROD_HPP_INC

#include "Queue.hpp"
#include "Signaler.hpp"

#include <sstream>

template<class T>
class Producer
{
  public:
    Producer(std::size_t amount,
             ConcQueue<T> & qu,
             Signaler const & s)
      : m_amount(amount)
      , m_targetQueue(qu)
      , m_signaler(s)
    {}
    Producer(Producer&&) = default;
    void run()
    {
      for ( std::size_t i = 0; i < m_amount; ++i )
      {
        int v = i;
        std::stringstream ss;
        ss << "Produced: " << v; 
        mutexedPrint(ss.str());
        m_targetQueue.push( v );
      }
      mutexedPrint("Producer DONE");
    }
  private:
    Producer(Producer&) = delete;
    void operator=(Producer&) = delete;
    std::size_t m_amount;
    ConcQueue<T> & m_targetQueue;
    Signaler const & m_signaler;
};

#endif
