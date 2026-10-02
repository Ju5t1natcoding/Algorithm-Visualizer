#include "../../core/states.hpp"

///the given array is of type mountain -> find the "highest" point in the array
void ternary_search(std::vector<int32_t>& a, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    int32_t l = 0, r = n - 1;

    while (r - l > 2) {
        int32_t mij1 = l + (r - l) / 3, mij2 = r - (r - l) / 3;

        if (a[mij1] < a[mij2]) {
            l = mij1;
        } else {
            r = mij2;
        }
    }

    int32_t best = l;
    for (int32_t i = l + 1; i <= r; ++i) {
        if (a[i] > a[best]) {
            best = i;
        }
    }
}