#include <MessageHandlerInterface.hpp>

using namespace igloo;

class MsgHandlerStub : public rahu::MessageHandlerInterface
{
  public:
    void receiveMessage(rahu::Message * m) {}
    void sendMessage(rahu::Message * m) {}
};

Context(a_message_handler)
{
  Spec(it_should_have_a_state)
  {
    Assert::That( mh.getState(), Equals( rahu::MessageHandlerInterface::IDLE ) );
  }

  Spec(state_can_be_set)
  {
    mh.setState( rahu::MessageHandlerInterface::WAITING );
    Assert::That( mh.getState(), Equals( rahu::MessageHandlerInterface::WAITING ) );
  }

  Spec(should_receive_and_send_messages)
  {
    rahu::Message * msg = 0;
    mh.receiveMessage(msg);
    mh.sendMessage(msg);
  }
  MsgHandlerStub mh;
};
