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
  std::vector<size_t> makeP(const std::string& word) {
    const size_t N(word.size());
    std::vector<size_t> P(N+1, 0);

    if (2 <= N) {
      size_t k = 0;

      for (size_t i = 1; i < N; ++i) {
        // word[0..i]
        // k is the computed P for word[0..i-1]
        const char c = word[i];
        while (k && (c != word[k]))
          k = P[k];
        if (c == word[k])
          ++k;
        P[i+1] = k;
      }
    }

    return P;
  }

  /** Returns the list of occurences of a non-empty pattern in the given text. */
  std::vector<size_t> search(const std::string& pattern, const std::string& text) {
    const size_t M(pattern.size());
    const size_t N(text.size());
    std::vector<size_t> result;    // list of occurences

    if (M && (M <= N)) {
      const std::vector<size_t> P(makeP(pattern));
      size_t j = 0;    // length of the matched pattern prefix

      for (size_t i=0; i+M <= N; ) {
        j = P[j];
        for (; (j < M) && (pattern[j] == text[i+j]); ++j);
        if (M == j)
          result.push_back(i);
        i += ((P[j] < j) ? (j - P[j]) : 1);
      }
    }

    return result;
  }

};
};
};

#endif
