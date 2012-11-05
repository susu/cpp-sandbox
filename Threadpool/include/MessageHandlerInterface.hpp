#ifndef RAHU_MH_INTERFACE_HPP_INC
#define RAHU_MH_INTERFACE_HPP_INC

#include <Message.hpp>

namespace rahu
{
  class MessageHandlerInterface
  {
    public:
      enum State
      {
        IDLE,
        WAITING
      };

      MessageHandlerInterface();
      virtual ~MessageHandlerInterface();

      State getState() const;
      void setState(State state);

      virtual void receiveMessage(Message * msg) = 0;
      virtual void sendMessage(Message * msg) = 0;
    private:
      State m_state;
  };
}

#endif
