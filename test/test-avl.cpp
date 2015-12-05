#include "../algo-all.h"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test-avl
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_avl_simple)
/* Compare with void free_test_function() */
{
    algocpp::avl<int> t;
    t.insert(1);
    t.insert(5);
    t.insert(7);
    t.insert(5);

    BOOST_CHECK(4==t.size());
}
