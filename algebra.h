#ifndef __ALGO__ALGEBRA__
#define __ALGO__ALGEBRA__

namespace algocpp {
namespace algebra {

  /**
   * Greatest common divisor. Can also be zero, if all the parameters
   * are zero.
   */
  template <class T> T gcd(T a, T b) {
    if ((a < 0) || (b < 0))
      return gcd(abs(a), abs(b));
    if (a < b)
      return gcd(b,a);
    if (0 == b)
      return a;
    return gcd(b, a % b);
  }

};
};

#endif
