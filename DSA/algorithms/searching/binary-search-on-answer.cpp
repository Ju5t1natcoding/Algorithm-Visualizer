#include "../../core/states.hpp"

void binary_search_on_answer(std::vector<int32_t>& a, int32_t m, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    int32_t mx = *std::max_element(a.begin(), a.end());
    int32_t l = 0, r = mx;

    auto verif = [&](int32_t x) -> bool {
        int32_t nr = 0;
        for (int32_t i = 0; i < n; ++i) {
            nr += std::max(0, a[i] - x);
        }

        return nr >= m;
    };

    while (l < r) {
        int32_t mij = l + ((r - l) >> 1);

        if (verif(mij)) {
            r = mij - 1;
        } else {
            l = mij;
        }
    }

    ///answer is in l
}