#include <iostream>
#include <map>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE test-avl
#include <boost/test/unit_test.hpp>

#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/generator_iterator.hpp>

#include "../algo-all.h"

BOOST_AUTO_TEST_CASE(test_avl_simple)
{
    algocpp::avl::avl<int> t;
    t.insert(1);
    t.insert(5);
    t.insert(7);
    t.insert(5);

    BOOST_CHECK_EQUAL(4, t.size());
    BOOST_CHECK_EQUAL(1, t.count(1));
    BOOST_CHECK_EQUAL(2, t.count(5));
    BOOST_CHECK_EQUAL(1, t.count(7));
    BOOST_CHECK_EQUAL(0, t.count(2));
}

BOOST_AUTO_TEST_CASE(test_avl_medium)
{
    const int lo =  -5;
    const int hi =  15;
    const unsigned int sz = 150;

    typedef boost::minstd_rand RNGType;
    RNGType rng(time(0));
    boost::uniform_int<int> distribution(lo,hi);
    boost::variate_generator<RNGType, boost::uniform_int<int> > dice(rng, distribution);
    algocpp::avl::avl<int> t;
    std::map<int,unsigned int> m;

    for (unsigned int i=0; i<sz; ++i) {
        int j = dice();

        std::map<int,unsigned int>::iterator it = m.find(j);
        if (m.end() == it) {
            m[j] = 1;
        } else {
            ++(it->second);
        }

        t.insert(j);
        BOOST_CHECK_EQUAL(1+i, t.size());
    }

    std::cerr << "AVL: " << t << std::endl;

    for (std::map<int,unsigned int>::iterator it = m.begin(); m.end() != it; ++it) {
        std::cerr << "Check: " << (it->first) << std::endl;
        BOOST_CHECK_EQUAL(it->second, t.count(it->first));
    }
    BOOST_CHECK_EQUAL(sz, t.size());
}

