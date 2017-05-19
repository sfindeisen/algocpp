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

  /**
   * Greatest common divisor. Can also be zero, if all the parameters
   * are zero.
   */
  template <class T> T gcd(T a, T b, T c) {
    return gcd(gcd(a,b),c);
  }

  /**
   * Greatest common divisor. Can also be zero, if all the parameters
   * are zero.
   */
  template <class T> T gcd(T a, T b, T c, T d) {
    return gcd(gcd(a,b),gcd(c,d));
  }

  /**
   * Least common multiple. Can also be zero, if at least 1 of the
   * parameters is zero.
   */
  template <class T> T lcm(T a, T b) {
    if ((0==a) || (0==b))
      return 0;
    return abs(a*b/gcd(a,b));
  }

  /**
   * Least common multiple. Can also be zero, if at least 1 of the
   * parameters is zero.
   */
  template <class T> T lcm(T a, T b, T c) {
    return lcm(lcm(a,b),c);
  }

  /**
   * Least common multiple. Can also be zero, if at least 1 of the
   * parameters is zero.
   */
  template <class T> T lcm(T a, T b, T c, T d) {
    return lcm(lcm(a,b),lcd(c,d));
  }

};
};

#endif
