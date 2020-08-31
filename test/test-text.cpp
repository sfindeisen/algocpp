#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test-text
#include <boost/test/unit_test.hpp>

#include "../text.h"

using namespace algocpp::text;

BOOST_AUTO_TEST_CASE(test_makeP) {
  {
    std::vector<size_t> expected_p {0};
    std::vector<int> p(kmp::makeP(""));
    BOOST_CHECK_EQUAL_COLLECTIONS(p.begin(), p.end(), expected_p.begin(), expected_p.end());
  }

  {
    std::vector<size_t> expected_p {0,0};
    std::vector<int> p(kmp::makeP("a"));
    BOOST_CHECK_EQUAL_COLLECTIONS(p.begin(), p.end(), expected_p.begin(), expected_p.end());
  }

  {
    std::vector<size_t> expected_p {0,0,0};
    std::vector<int> p(kmp::makeP("ab"));
    BOOST_CHECK_EQUAL_COLLECTIONS(p.begin(), p.end(), expected_p.begin(), expected_p.end());
  }

  {
    std::vector<size_t> expected_p {0,0,1};
    std::vector<int> p(kmp::makeP("aa"));
    BOOST_CHECK_EQUAL_COLLECTIONS(p.begin(), p.end(), expected_p.begin(), expected_p.end());
  }

  {
    std::vector<size_t> expected_p {0,0,1,0};
    std::vector<int> p(kmp::makeP("aab"));
    BOOST_CHECK_EQUAL_COLLECTIONS(p.begin(), p.end(), expected_p.begin(), expected_p.end());
  }

  {
    std::vector<size_t> expected_p {0,0,0,0};
    std::vector<int> p(kmp::makeP("abb"));
    BOOST_CHECK_EQUAL_COLLECTIONS(p.begin(), p.end(), expected_p.begin(), expected_p.end());
  }

  {
    std::vector<size_t> expected_p {0,0,0,1};
    std::vector<int> p(kmp::makeP("aba"));
    BOOST_CHECK_EQUAL_COLLECTIONS(p.begin(), p.end(), expected_p.begin(), expected_p.end());
  }

  {
    std::vector<size_t> expected_p {0,0,0,1,2,3};
    std::vector<int> p(kmp::makeP("ababa"));
    BOOST_CHECK_EQUAL_COLLECTIONS(p.begin(), p.end(), expected_p.begin(), expected_p.end());
  }

  {
    std::vector<size_t> expected_p {0,0,1,2,3,4};
    std::vector<int> p(kmp::makeP("aaaaa"));
    BOOST_CHECK_EQUAL_COLLECTIONS(p.begin(), p.end(), expected_p.begin(), expected_p.end());
  }
}
