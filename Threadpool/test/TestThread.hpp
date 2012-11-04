#include <igloo/igloo.h>

#include <Thread.hpp>

class DummyThread : public rahu::Thread
{
  public:
    DummyThread()
      : m_ran(false)
    {}
    virtual ~DummyThread()
    {}
    bool isRan() const
    {
      return m_ran;
    }
    std::thread::id getRunnerThreadId() const
    {
      return m_runnerThreadId;
    }
  protected:
    virtual void run()
    {
      m_ran = true;
      m_runnerThreadId = std::this_thread::get_id();
    }
  private:
    bool m_ran;
    std::thread::id m_runnerThreadId;
};

using namespace igloo;

Context(a_thread)
{
  Spec(should_run_on_separate_thread)
  {
    thread.start();
    thread.join();

    Assert::That( thread.isRan(), Equals(true));
    Assert::That( thread.getRunnerThreadId(), !Equals(std::this_thread::get_id()) );
  }
  DummyThread thread;
};
