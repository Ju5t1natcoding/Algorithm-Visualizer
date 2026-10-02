#include "../../core/states.hpp"

void binary_search(std::vector<int32_t>& a, int32_t target, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    int32_t l = 0, r = n - 1;

    while (l < r) {
        int32_t mij = l + ((r - l) >> 1);

        if (a[mij] <= target) {
            l = mij;
        } else {
            r = mij - 1;
        }
    }

    ///answer is in l
}