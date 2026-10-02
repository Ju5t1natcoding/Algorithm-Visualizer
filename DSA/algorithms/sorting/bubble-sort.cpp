#include "../../core/states.hpp"

void bubble_sort(std::vector<int32_t>& a, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = i + 1; j < n; ++j) {
            if (a[i] > a[j]) {
                std::swap(a[i], a[j]);
            }
        }
    }
}