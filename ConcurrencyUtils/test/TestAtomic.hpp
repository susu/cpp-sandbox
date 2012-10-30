#include <igloo/igloo.h>
#include <Atomic.hpp>

using namespace igloo;

Context(an_atomic_variable)
{
  an_atomic_variable()
    : atomic(10)
  {}

  void SetUp()
  {
    atomic.store(344u);
  }

  Spec(ctor_set_a_value)
  {
    rahu::Atomic lAtomic(10u);
    Assert::That( lAtomic.load(), Equals( 10u ) );
  }

  Spec(it_should_store_and_return_the_value)
  {
    atomic.store(67u);
    rahu::Atomic::Value res = atomic.load();
    Assert::That( res, Equals( 67u ) );
  }

  Spec(cmpSwap_should_swap_if_value_equals_to_cmp)
  {
    rahu::Atomic::Value with = 19u;
    rahu::Atomic::Value cmp = 344u;
    atomic.cmpSwap(cmp, with);
    Assert::That( atomic.load(), Equals( 19u ) );
  }

  Spec(cmpSwap_should_not_swap_if_values_differs)
  {
    rahu::Atomic::Value with = 15u;
    rahu::Atomic::Value cmp = 88u;
    atomic.cmpSwap(cmp,with);
    Assert::That( atomic.load(), Equals(344u) );
  }

  Spec(cmpSwap_should_return_the_old_value)
  {
    // Arrange
    rahu::Atomic::Value with = 19u;
    rahu::Atomic::Value cmp = 3u;
    // Act
    rahu::Atomic::Value res = atomic.cmpSwap(cmp, with);
    // Assert
    Assert::That( res, Equals( 344u ) );
  }
  rahu::Atomic atomic;
};

