
#include "Consumer.hpp"
#include "Producer.hpp"
#include "Signaler.hpp"
#include "Queue.hpp"

#include <thread>
#include <iostream>
#include <vector>
#include <algorithm>

#include <unistd.h>

int main()
{
  const int PROD_NUM = 1;
  const int CONS_NUM = 10;
  const int MSG_PER_PROD = 100;
  typedef int MsgType;
  std::vector<Producer<MsgType>> m_prods;
  std::vector<Consumer<MsgType>> m_cons;
  ConcQueue<MsgType> theQ;
  Signaler & si = theQ.getSignaler();

  std::generate_n(std::back_inserter(m_prods),PROD_NUM,
    [&theQ,&si]()
  {
    return Producer<MsgType>(MSG_PER_PROD, theQ, si);
  });

  int startId = 0;
  std::generate_n(std::back_inserter(m_cons),CONS_NUM,
    [&theQ,&si,&startId]()
  {
    ++startId;
    return Consumer<MsgType>(startId, theQ, si);
  });

  std::vector<std::thread> m_threads;
  for ( auto & prod : m_prods )
  {
    m_threads.push_back(
      std::thread( &Producer<MsgType>::run, &prod ) );
  }
  for ( auto & cons : m_cons )
  {
    m_threads.push_back(
      std::thread( &Consumer<MsgType>::run, &cons ) );
  }

  // TODO async timer/sleeping
  sleep(3);
  std::cout << "OverTime, signaling" << std::endl;
  si.fireSignal( Signaler::SHUTDOWN );
  for ( auto & thr : m_threads )
  {
    if ( thr.joinable() )
    {
      thr.join();
    }
  }

}
