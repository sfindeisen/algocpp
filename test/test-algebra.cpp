#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test-algebra
#include <boost/test/unit_test.hpp>

#include "../algebra.h"
#include "utils.h"

BOOST_AUTO_TEST_CASE(test_gcd2) {
    BOOST_CHECK_EQUAL(5, algocpp::algebra::gcd(5,15));
    BOOST_CHECK_EQUAL(1, algocpp::algebra::gcd(5,7));
    BOOST_CHECK_EQUAL(5, algocpp::algebra::gcd(10,15));
    BOOST_CHECK_EQUAL(5, algocpp::algebra::gcd(10,-15));
    BOOST_CHECK_EQUAL(5, algocpp::algebra::gcd(-10,15));
    BOOST_CHECK_EQUAL(7, algocpp::algebra::gcd(7,0));
    BOOST_CHECK_EQUAL(1, algocpp::algebra::gcd(1,0));
    BOOST_CHECK_EQUAL(7, algocpp::algebra::gcd(0,7));
    BOOST_CHECK_EQUAL(1, algocpp::algebra::gcd(0,1));
    BOOST_CHECK_EQUAL(0, algocpp::algebra::gcd(0,0));

    BOOST_CHECK_EQUAL(8*7, algocpp::algebra::gcd(16*3*7*7, 8*5*7*17));
}

BOOST_AUTO_TEST_CASE(test_gcd2_long) {
    BOOST_CHECK_EQUAL(5L, algocpp::algebra::gcd(5L,15L));
    BOOST_CHECK_EQUAL(1L, algocpp::algebra::gcd(5L,7L));
    BOOST_CHECK_EQUAL(5L, algocpp::algebra::gcd(10L,15L));
    BOOST_CHECK_EQUAL(5L, algocpp::algebra::gcd(10L,-15L));
    BOOST_CHECK_EQUAL(5L, algocpp::algebra::gcd(-10L,15L));
    BOOST_CHECK_EQUAL(7L, algocpp::algebra::gcd(7L,0L));
    BOOST_CHECK_EQUAL(1L, algocpp::algebra::gcd(1L,0L));
    BOOST_CHECK_EQUAL(7L, algocpp::algebra::gcd(0L,7L));
    BOOST_CHECK_EQUAL(1L, algocpp::algebra::gcd(0L,1L));
    BOOST_CHECK_EQUAL(0L, algocpp::algebra::gcd(0L,0L));

    BOOST_CHECK_EQUAL(8*7L, algocpp::algebra::gcd(16*3*7*7L, 8*5*7*17L));
}

BOOST_AUTO_TEST_CASE(test_gcd3) {
    BOOST_CHECK_EQUAL(5, algocpp::algebra::gcd(5,15,35));
    BOOST_CHECK_EQUAL(5, algocpp::algebra::gcd(5,35,15));
    BOOST_CHECK_EQUAL(5, algocpp::algebra::gcd(5,15,15));
    BOOST_CHECK_EQUAL(5, algocpp::algebra::gcd(5,15,5));
    BOOST_CHECK_EQUAL(5, algocpp::algebra::gcd(5,5,15));

    BOOST_CHECK_EQUAL(1, algocpp::algebra::gcd(7,5,5));
    BOOST_CHECK_EQUAL(1, algocpp::algebra::gcd(5,7,5));
    BOOST_CHECK_EQUAL(1, algocpp::algebra::gcd(5,5,7));

    BOOST_CHECK_EQUAL(1, algocpp::algebra::gcd(1,0,0));
    BOOST_CHECK_EQUAL(1, algocpp::algebra::gcd(0,1,0));
    BOOST_CHECK_EQUAL(1, algocpp::algebra::gcd(0,0,1));

    BOOST_CHECK_EQUAL(2*7, algocpp::algebra::gcd(16*3*7*7, 8*5*7*17, 2*3*5*7));
}

template <class T> static void verify_gcd_ext(const T expected_gcd, const T a, const T b) {
    // sanity check
    if (expected_gcd) {
        BOOST_CHECK_EQUAL(0, a % expected_gcd);
        BOOST_CHECK_EQUAL(0, b % expected_gcd);
    }

    const std::tuple<T,T,T> w(algocpp::algebra::gcd_ext(a, b));
    BOOST_CHECK_EQUAL(expected_gcd, std::get<0>(w));
    BOOST_CHECK_EQUAL(expected_gcd, a * std::get<1>(w) + b * std::get<2>(w));
}

BOOST_AUTO_TEST_CASE(test_gcd2_ext) {
    verify_gcd_ext(5,   5,  15);
    verify_gcd_ext(1,   5,   7);
    verify_gcd_ext(5,  10,  15);
    verify_gcd_ext(5,  10, -15);
    verify_gcd_ext(5, -10,  15);
    verify_gcd_ext(5, -10, -15);
    verify_gcd_ext(7,   7,   0);
    verify_gcd_ext(1,   1,   0);
    verify_gcd_ext(7,   0,   7);
    verify_gcd_ext(1,   0,   1);
    verify_gcd_ext(0,   0,   0);

    verify_gcd_ext(8*7, 16*3*7*7, 8*5*7*17);
}

BOOST_AUTO_TEST_CASE(test_lcm2) {
    BOOST_CHECK_EQUAL(15,    algocpp::algebra::lcm( 5,15));
    BOOST_CHECK_EQUAL(15,    algocpp::algebra::lcm(-5,15));
    BOOST_CHECK_EQUAL(15,    algocpp::algebra::lcm( 5,-15));
    BOOST_CHECK_EQUAL(15,    algocpp::algebra::lcm(-5,-15));
    BOOST_CHECK_EQUAL(15,    algocpp::algebra::lcm( 1,15));
    BOOST_CHECK_EQUAL(15*17, algocpp::algebra::lcm(15,17));
    BOOST_CHECK_EQUAL(15*17, algocpp::algebra::lcm(15,-17));
    BOOST_CHECK_EQUAL(0,     algocpp::algebra::lcm( 0,15));

    BOOST_CHECK_EQUAL(16*3*5*7*7*17, algocpp::algebra::lcm(16*3*7*7, 8*5*7*17));
}
