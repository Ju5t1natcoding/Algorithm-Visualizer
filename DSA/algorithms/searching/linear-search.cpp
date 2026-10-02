#include "../../core/states.hpp"

void linear_search(std::vector<int32_t>& a, int32_t target, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    std::vector<int32_t> poz;

    for (int i = 0; i < n; ++i) {
        if (a[i] == target) {
            poz.push_back(i);
        }
    }
}