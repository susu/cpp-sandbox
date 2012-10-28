#include <cxxtest/TestSuite.h>

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

class TestThread : public CxxTest::TestSuite
{
  public:
    void test_it_should_run_on_separate_thread()
    {
      // Arrange
      DummyThread thr;
      // Act
      thr.start();
      thr.join();
      // Assert
      TS_ASSERT( thr.isRan() );
      TS_ASSERT_DIFFERS( thr.getRunnerThreadId(), std::this_thread::get_id() );
      thr.join();
    }
};
