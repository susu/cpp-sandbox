#ifndef RAHU_ATOMIC_HPP_INC
#define RAHU_ATOMIC_HPP_INC

#include <boost/interprocess/detail/atomic.hpp>


namespace rahu
{
  class Atomic
  {
    public:
      typedef boost::uint32_t Value;
      Atomic(Value initialValue);

      void store(Value val);
      Value load();
      Value cmpSwap(Value cmp, Value with);
    private:
      Value m_value;
  };
}
#endif
