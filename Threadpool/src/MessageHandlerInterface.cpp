#include <MessageHandlerInterface.hpp>

rahu::MessageHandlerInterface::MessageHandlerInterface()
  : m_state(IDLE)
{}

rahu::MessageHandlerInterface::~MessageHandlerInterface()
{}

rahu::MessageHandlerInterface::State
rahu::MessageHandlerInterface::getState() const
{
  return m_state;
}

void
rahu::MessageHandlerInterface::setState(State state)
{
  m_state = state;
}

