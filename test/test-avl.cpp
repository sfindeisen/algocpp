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
#include "utils.h"

// random number generator type
typedef boost::minstd_rand RNGType;
typedef boost::variate_generator<RNGType, boost::uniform_int<int> > tdice;

const int Lo =  -5;
const int Hi =  15;

using namespace algocpp::avl;

template <class T> std::map<T,size_t> avl2map(const avl<T>& tree) {
    return vector2map(std::vector<T>(tree.begin(), tree.end()));
}

tdice create_rng() {
    RNGType rng(time(0));
    boost::uniform_int<int> distribution(Lo,Hi);
    return tdice(rng, distribution);
}

template <class T> void test_iter(const avl<T>& tree) {
    const int k=tree.size();
    int i=0;
    T t;

    for (typename avl<T>::const_iterator it = tree.begin(); tree.end() != it; ++i,++it) {
        T v = *it;
        if (1 <= i)
            BOOST_CHECK(t <= v);
        t = v;
    }

    BOOST_CHECK_EQUAL(k,i);
}

template <class T> void test_insert_random(tdice& dice, avl<T>& tree, const size_t& count) {
    const std::vector<T> vec(tree.begin(), tree.end());
    std::map<T,size_t> m(avl2map(tree));
    BOOST_CHECK_EQUAL(vec.size(), tree.size());

    for (size_t i=0; i<count; ++i) {
        int j = dice();

        typename std::map<T,size_t>::iterator it = m.find(j);
        if (m.end() == it) {
            m[j] = 1;
        } else {
            ++(it->second);
        }

        tree.insert(j);
        BOOST_CHECK_EQUAL(1+i+vec.size(), tree.size());
    }

    // std::cerr << "AVL: " << tree << std::endl;
    test_iter<T>(tree);

    for (typename std::map<T,size_t>::iterator it = m.begin(); m.end() != it; ++it) {
        // std::cerr << "Check: " << (it->first) << std::endl;
        BOOST_CHECK_EQUAL(it->second, tree.count(it->first));
    }
    BOOST_CHECK_EQUAL(count+vec.size(), tree.size());
}

template <class T> void test_remove_random(tdice& dice, avl<T>& tree, const size_t& count) {
    std::vector<T> vec(tree.begin(), tree.end());
    BOOST_CHECK_EQUAL(vec.size(), tree.size());

    for (size_t i=0; (i < count) && (! vec.empty()); ++i) {
        const int j = dice() % vec.size();
        tree.remove(vec[j]);
        vec[j]=vec[vec.size()-1];
        vec.pop_back();
    }

    // std::cerr << "AVL: " << tree << std::endl;
    test_iter<T>(tree);
}

BOOST_AUTO_TEST_CASE(test_avl_simple) {
    avl<int> t;
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

BOOST_AUTO_TEST_CASE(test_avl_example) {
    avl<int> t;
    t.insert(1);
    t.insert(5);
    t.insert(7);
    t.insert(5);
    t.remove(5);        // element remove
    t.insert(18);
    t.insert(5);

    BOOST_CHECK_EQUAL(5, t.size());
    BOOST_CHECK_EQUAL(1, t.count(1));
    BOOST_CHECK_EQUAL(2, t.count(5));
    BOOST_CHECK_EQUAL(1, t.count(7));
    BOOST_CHECK_EQUAL(1, t.count(18));
    BOOST_CHECK_EQUAL(0, t.count(2));

    std::vector<int> vec(t.begin(), t.end());
}

BOOST_AUTO_TEST_CASE(test_avl_insert_some) {
    tdice dice(create_rng());
    avl<int> avl;
    test_insert_random<int>(dice, avl, 150);
}

BOOST_AUTO_TEST_CASE(test_avl_medium) {
    tdice dice(create_rng());
    avl<int> avl;
    test_insert_random<int>(dice, avl, 150);
    test_remove_random<int>(dice, avl, 120);
    test_insert_random<int>(dice, avl, 150);
}
