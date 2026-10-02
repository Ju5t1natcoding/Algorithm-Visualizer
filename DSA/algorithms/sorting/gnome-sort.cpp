#include "../../core/states.hpp"

void gnome_sort(std::vector<int32_t>& a, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    int32_t poz = 1;

    while (poz < n) {
        if (!poz || a[poz] >= a[poz - 1]) {
            poz++;
        } else {
            std::swap(a[poz], a[poz - 1]);
            poz--;
        }
    }
}