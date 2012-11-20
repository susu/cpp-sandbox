#ifndef UTILS_ENFORCE
#define UTILS_ENFORCE


// READIT: http://www.drdobbs.com/enforcements/184403864

namespace utils
{
  template<class E,class A>
  inline void enforce(bool condition, A arg)
  {
    if (!condition) throw E(arg);
  }
}

#endif
