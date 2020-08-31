#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test-text
#include <boost/test/unit_test.hpp>

#include "../text.h"

using namespace algocpp::text;

BOOST_AUTO_TEST_CASE(test_makeP) {
  {
    std::vector<size_t> expected_p {0};
    std::vector<size_t> p(kmp::makeP(""));
    BOOST_CHECK_EQUAL_COLLECTIONS(p.begin(), p.end(), expected_p.begin(), expected_p.end());
  }

  {
    std::vector<size_t> expected_p {0,0};
    std::vector<size_t> p(kmp::makeP("a"));
    BOOST_CHECK_EQUAL_COLLECTIONS(p.begin(), p.end(), expected_p.begin(), expected_p.end());
  }

  {
    std::vector<size_t> expected_p {0,0,0};
    std::vector<size_t> p(kmp::makeP("ab"));
    BOOST_CHECK_EQUAL_COLLECTIONS(p.begin(), p.end(), expected_p.begin(), expected_p.end());
  }

  {
    std::vector<size_t> expected_p {0,0,1};
    std::vector<size_t> p(kmp::makeP("aa"));
    BOOST_CHECK_EQUAL_COLLECTIONS(p.begin(), p.end(), expected_p.begin(), expected_p.end());
  }

  {
    std::vector<size_t> expected_p {0,0,1,0};
    std::vector<size_t> p(kmp::makeP("aab"));
    BOOST_CHECK_EQUAL_COLLECTIONS(p.begin(), p.end(), expected_p.begin(), expected_p.end());
  }

  {
    std::vector<size_t> expected_p {0,0,0,0};
    std::vector<size_t> p(kmp::makeP("abb"));
    BOOST_CHECK_EQUAL_COLLECTIONS(p.begin(), p.end(), expected_p.begin(), expected_p.end());
  }

  {
    std::vector<size_t> expected_p {0,0,0,1};
    std::vector<size_t> p(kmp::makeP("aba"));
    BOOST_CHECK_EQUAL_COLLECTIONS(p.begin(), p.end(), expected_p.begin(), expected_p.end());
  }

  {
    std::vector<size_t> expected_p {0,0,0,1,2,3};
    std::vector<size_t> p(kmp::makeP("ababa"));
    BOOST_CHECK_EQUAL_COLLECTIONS(p.begin(), p.end(), expected_p.begin(), expected_p.end());
  }

  {
    std::vector<size_t> expected_p {0,0,1,2,3,4};
    std::vector<size_t> p(kmp::makeP("aaaaa"));
    BOOST_CHECK_EQUAL_COLLECTIONS(p.begin(), p.end(), expected_p.begin(), expected_p.end());
  }
}

BOOST_AUTO_TEST_CASE(test_search) {
  // Fibonacci words are:
  //
  //   a
  //   b
  //   ab
  //   aba
  //   abaab
  //   abaababa
  //   abaababaabaab
  //   abaababaabaababaababa
  //   abaababaabaababaababaabaababaabaab
  //   ...

  {
    std::vector<size_t> expected_occ {};
    std::vector<size_t> occ(kmp::search("", ""));
    BOOST_CHECK_EQUAL_COLLECTIONS(occ.begin(), occ.end(), expected_occ.begin(), expected_occ.end());
  }

  {
    std::vector<size_t> expected_occ {};
    std::vector<size_t> occ(kmp::search("a", ""));
    BOOST_CHECK_EQUAL_COLLECTIONS(occ.begin(), occ.end(), expected_occ.begin(), expected_occ.end());
  }

  {
    std::vector<size_t> expected_occ {};
    std::vector<size_t> occ(kmp::search("", "a"));
    BOOST_CHECK_EQUAL_COLLECTIONS(occ.begin(), occ.end(), expected_occ.begin(), expected_occ.end());
  }

  {
    std::vector<size_t> expected_occ {0};
    std::vector<size_t> occ(kmp::search("a", "a"));
    BOOST_CHECK_EQUAL_COLLECTIONS(occ.begin(), occ.end(), expected_occ.begin(), expected_occ.end());
  }

  {
    std::vector<size_t> expected_occ {0,1};
    std::vector<size_t> occ(kmp::search("a", "aa"));
    BOOST_CHECK_EQUAL_COLLECTIONS(occ.begin(), occ.end(), expected_occ.begin(), expected_occ.end());
  }

  {
    std::vector<size_t> expected_occ {0,1,2};
    std::vector<size_t> occ(kmp::search("a", "aaa"));
    BOOST_CHECK_EQUAL_COLLECTIONS(occ.begin(), occ.end(), expected_occ.begin(), expected_occ.end());
  }

  {
    std::vector<size_t> expected_occ {0,1,2,3};
    std::vector<size_t> occ(kmp::search("aa", "aaaaa"));
    BOOST_CHECK_EQUAL_COLLECTIONS(occ.begin(), occ.end(), expected_occ.begin(), expected_occ.end());
  }

  {
    std::vector<size_t> expected_occ {0,2,4};
    std::vector<size_t> occ(kmp::search("ab", "ababab"));
    BOOST_CHECK_EQUAL_COLLECTIONS(occ.begin(), occ.end(), expected_occ.begin(), expected_occ.end());
  }

  {
    std::vector<size_t> expected_occ {2,6,9,14};
    std::vector<size_t> occ(kmp::search("ab", "aaabaaabcabaaaabd"));
    BOOST_CHECK_EQUAL_COLLECTIONS(occ.begin(), occ.end(), expected_occ.begin(), expected_occ.end());
  }

  {
    std::vector<size_t> expected_occ {0,2};
    std::vector<size_t> occ(kmp::search("aba", "ababab"));
    BOOST_CHECK_EQUAL_COLLECTIONS(occ.begin(), occ.end(), expected_occ.begin(), expected_occ.end());
  }

  {
    std::vector<size_t> occ(kmp::search("a", "abaababaabaababaababaabaababaabaab"));
    BOOST_CHECK_EQUAL(21, occ.size());
  }

  {
    std::vector<size_t> expected_occ {0,3,5,8,11,13,16,18,21,24,26,29};
    std::vector<size_t> occ(kmp::search("aba", "abaababaabaababaababaabaababaabaab"));
    BOOST_CHECK_EQUAL_COLLECTIONS(occ.begin(), occ.end(), expected_occ.begin(), expected_occ.end());
  }

  {
    std::vector<size_t> expected_occ {0,5,8,13,18,21,26,29};
    std::vector<size_t> occ(kmp::search("abaa", "abaababaabaababaababaabaababaabaab"));
    BOOST_CHECK_EQUAL_COLLECTIONS(occ.begin(), occ.end(), expected_occ.begin(), expected_occ.end());
  }

  {
    std::vector<size_t> expected_occ {3,6};
    std::vector<size_t> occ(kmp::search("abaa", "zxcabaabaa"));
    BOOST_CHECK_EQUAL_COLLECTIONS(occ.begin(), occ.end(), expected_occ.begin(), expected_occ.end());
  }

  {
    std::vector<size_t> expected_occ {3,6};
    std::vector<size_t> occ(kmp::search("abaa", "zxcabaabaac"));
    BOOST_CHECK_EQUAL_COLLECTIONS(occ.begin(), occ.end(), expected_occ.begin(), expected_occ.end());
  }

  {
    std::vector<size_t> expected_occ {3,7};
    std::vector<size_t> occ(kmp::search("abaa", "zxcabaaabaa"));
    BOOST_CHECK_EQUAL_COLLECTIONS(occ.begin(), occ.end(), expected_occ.begin(), expected_occ.end());
  }

  {
    std::vector<size_t> expected_occ {3,7};
    std::vector<size_t> occ(kmp::search("abaa", "zxcabaaabaac"));
    BOOST_CHECK_EQUAL_COLLECTIONS(occ.begin(), occ.end(), expected_occ.begin(), expected_occ.end());
  }

  {
    std::vector<size_t> expected_occ {3,8};
    std::vector<size_t> occ(kmp::search("abaa", "zxcabaacabaa"));
    BOOST_CHECK_EQUAL_COLLECTIONS(occ.begin(), occ.end(), expected_occ.begin(), expected_occ.end());
  }

  {
    std::vector<size_t> expected_occ {3,8};
    std::vector<size_t> occ(kmp::search("abaa", "zxcabaacabaac"));
    BOOST_CHECK_EQUAL_COLLECTIONS(occ.begin(), occ.end(), expected_occ.begin(), expected_occ.end());
  }

  {
    std::vector<size_t> expected_occ {};
    std::vector<size_t> occ(kmp::search("s", "zxcabaacabaac"));
    BOOST_CHECK_EQUAL_COLLECTIONS(occ.begin(), occ.end(), expected_occ.begin(), expected_occ.end());
  }

  {
    std::vector<size_t> expected_occ {0};
    std::vector<size_t> occ(kmp::search("z", "zxcabaacabaac"));
    BOOST_CHECK_EQUAL_COLLECTIONS(occ.begin(), occ.end(), expected_occ.begin(), expected_occ.end());
  }

  {
    std::vector<size_t> expected_occ {1};
    std::vector<size_t> occ(kmp::search("x", "zxcabaacabaac"));
    BOOST_CHECK_EQUAL_COLLECTIONS(occ.begin(), occ.end(), expected_occ.begin(), expected_occ.end());
  }

  {
    std::vector<size_t> expected_occ {2,7,12};
    std::vector<size_t> occ(kmp::search("c", "zxcabaacabaac"));
    BOOST_CHECK_EQUAL_COLLECTIONS(occ.begin(), occ.end(), expected_occ.begin(), expected_occ.end());
  }
}
