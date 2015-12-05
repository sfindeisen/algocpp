# Algorithms + data structures in C++

A lightweight and easy to use implementation that can be used as a drop-in supplement to STL. 100% STL compatible. Designed with programming competitions in mind.

## Features

* AVL trees

## Example

```
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
```
