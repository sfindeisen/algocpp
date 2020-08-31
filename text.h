#ifndef __ALGO__TEXT__
#define __ALGO__TEXT__

#include <string>

namespace algocpp {
namespace text {
namespace kmp {

  /********************************/
  /* Knuth-Morris-Pratt algorithm */
  /********************************/

  /**
   * Given a word, computes its P array. Resulting P[i+1] is the length of the longest proper prefix
   * of the prefix word[0..i], which is also its (proper) suffix. The resulting P array is 1 longer
   * than the input word.
   *
   * Thus:
   *
   *   P[0] == 0; corresponds to the empty prefix
   *   P[1] == 0; corresponds to the 1-element prefix word[0..0]
   *   P[N] is the length of the longest proper prefix and suffix of the input word.
   */
  std::vector<int> makeP(const std::string& word) {
    const size_t N(word.size());
    std::vector<int> p(N+1, 0);

    if (2 <= N) {
      size_t k = 0;

      for (size_t i = 1; i < N; ++i) {
        // k is the length of the longest proper prefix and suffix of word[0..i-1]
        const char c = word[i];
        while (k && (c != word[k]))
          k = p[k];
        if (c == word[k])
          ++k;
        p[i+1] = k;
      }
    }

    return p;
  }

};
};
};

#endif
