#include <Atomic.hpp>

using namespace boost::interprocess::ipcdetail;

rahu::Atomic::Atomic(Value val)
{
  store(val);
}

void
rahu::Atomic::store(Value val)
{
  atomic_write32(&m_value, val);
}

rahu::Atomic::Value
rahu::Atomic::load()
{
  return atomic_read32(&m_value);
}

rahu::Atomic::Value
rahu::Atomic::cmpSwap(Value cmp, Value with)
{
  return atomic_cas32(&m_value, with, cmp);
}
