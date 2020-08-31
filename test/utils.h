#ifndef __ALGO__TEST_UTILS__
#define __ALGO__TEST_UTILS__

#include <map>
#include <vector>

using namespace std;

template <class T> map<T,size_t> vector2map(const vector<T>& u) {
    map<T,size_t> m;

    for (typename vector<T>::const_iterator itv = u.begin(); u.end() != itv; ++itv) {
        typename map<T,size_t>::iterator itm = m.find(*itv);
        if (m.end() == itm) {
            m[*itv] = 1;
        } else {
            ++(itm->second);
        }
    }

    return m;
}

#endif
