#include "../../core/states.hpp"

void insertion_sort(std::vector<int32_t>& a, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    for (int32_t i = 1; i < n; ++i) {
        int32_t k = a[i];
        int32_t j = i - 1;

        while (j >= 0 && a[j] > k) {
            a[j + 1] = a[j];
            --j;
        }

        a[j + 1] = k;
    }
}