#include <Thread.hpp>

rahu::Thread::Thread()
{
}

rahu::Thread::~Thread()
{}

void
rahu::Thread::start()
{
  m_thread = std::thread( &Thread::run, this );
}

void
rahu::Thread::join()
{
  if (m_thread.joinable())
  {
    m_thread.join();
  }
}
