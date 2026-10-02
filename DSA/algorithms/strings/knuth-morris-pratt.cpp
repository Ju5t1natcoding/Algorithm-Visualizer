#include "../../core/states.hpp"

void knuth_morris_pratt(std::string& s, std::string& t, std::vector<State>& states) { ///KMP
    int32_t n = static_cast<int32_t>(s.size()), m = static_cast<int32_t>(t.size());
    std::vector<int32_t> lps(m, 0), v;
    int32_t q = 0;
    lps[0] = 0;

    for (int i = 1; i < m; ++i) {
        while (q && t[i] != t[q]) {
            q = lps[q - 1];
        }

        if (t[i] == t[q]) {
            q++;
        }

        lps[i] = q;
    }

    for (int i = 0; i < n; ++i) {
        while (q && s[i] != t[q]) {
            q = lps[q - 1];
        }

        if (s[i] == t[q]) {
            q++;
        }

        if (q == m) {
            v.push_back(i - m + 1);
            q = lps[q - 1];
        }
    }
}