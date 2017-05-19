#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test-algebra
#include <boost/test/unit_test.hpp>

#include "../algo-all.h"
#include "utils.h"

BOOST_AUTO_TEST_CASE(test_gcd_simple) {
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
    BOOST_CHECK_EQUAL(8*7, algocpp::algebra::gcd(16*3*7*7,8*5*7*17));
}
