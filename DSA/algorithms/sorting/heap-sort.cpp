#include "../../core/states.hpp"

void heapsort(std::vector<int32_t>& a, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    int32_t start = n >> 1, end = n;

    while (end > 1) {
        if (start) {
            start--;
        } else {
            end--;
            std::swap(a[0], a[end]);
        }

        int32_t rad = start;

        while ((rad << 1) < end) {
            int32_t ch = rad << 1;

            if (ch + 1 < end && a[ch] < a[ch + 1]) {
                ch++;
            }

            if (a[rad] < a[ch]) {
                std::swap(a[rad], a[ch]);
                rad = ch;
            } else {
                break;
            }
        }
    }
}