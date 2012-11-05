#include <igloo/igloo.h>
#include "TestThread.hpp"
#include "TestMessageHandlerInterface.hpp"

int main()
{
  return igloo::TestRunner::RunAllTests();
}
