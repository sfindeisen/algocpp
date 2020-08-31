#include <tuple>

#ifndef __ALGO__ALGEBRA__
#define __ALGO__ALGEBRA__

namespace algocpp {
namespace algebra {

  /** absolute value */
  template <class T> inline T abs(T x) {
    return ((0 <= x) ? x : (-x));
  }

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
   * Greatest common divisor (extended version). Given a and b, returns a
   * tuple (g,x,y) such that:
   *
   *   g = gcd(a,b) = ax + by
   */
  template <class T> std::tuple<T,T,T> gcd_ext(T a, T b) {
    if (a < 0) {
      const std::tuple<T,T,T> w(gcd_ext(-a, b));
      return std::make_tuple(std::get<0>(w), 0 - std::get<1>(w), std::get<2>(w));
    }
    if (b < 0) {
      const std::tuple<T,T,T> w(gcd_ext(a, -b));
      return std::make_tuple(std::get<0>(w), std::get<1>(w), 0 - std::get<2>(w));
    }
    if (a < b) {
      const std::tuple<T,T,T> w(gcd_ext(b, a));
      return std::make_tuple(std::get<0>(w), std::get<2>(w), std::get<1>(w));
    }
    if (0 == b)
      return std::make_tuple(a,1,0);

    // Here: 0 < b <= a

    const T q(a / b);
    const T r(a % b);

    const std::tuple<T,T,T> w(gcd_ext(b, r));
    return std::make_tuple(std::get<0>(w), std::get<2>(w), std::get<1>(w) - q * std::get<2>(w));
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
