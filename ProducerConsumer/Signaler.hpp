#ifndef SIGNALER_HPP_INC
#define SIGNALER_HPP_INC

#include <array>

class Signaler
{
  public:
    enum SignalType
    {
      MIN = 0,
      SHUTDOWN = 0,
      MAX = 1
    };
    Signaler(std::condition_variable & cv)
      : m_notif(cv)
    {
      for( auto & i : m_signals )
        i = false;
    }
    Signaler(Signaler&) = delete;
    void operator=(Signaler&) = delete;
    bool isSignaled( SignalType s ) const
    {
      return m_signals[s];
    }
    void fireSignal( SignalType s )
    {
      m_signals[s] = true;
      m_notif.notify_all();
    }
  private:
    std::array<bool,MAX> m_signals;
    std::condition_variable & m_notif;
};

#endif

