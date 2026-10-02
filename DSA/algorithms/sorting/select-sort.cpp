#include "../../core/states.hpp"

void select_sort(std::vector<int32_t>& a, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    for (int32_t i = 0; i < n; ++i) {
        int32_t pm = i;
        for (int32_t j = i + 1; j < n; ++j) {
            if (a[j] < a[pm]) {
                pm = j;
            }
        }

        if (pm != i) {
            std::swap(a[i], a[pm]);
        }
    }
}