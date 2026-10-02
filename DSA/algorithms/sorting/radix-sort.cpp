#include "../../core/states.hpp"

void radix_sort_base_256(std::vector<int32_t>& a, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());

    if (n <= 1) {
        return;
    }

    std::vector<int32_t> fr(256, 0), v(n);
    for (int32_t pas = 0; pas < 4; ++pas) {
        fill(fr.begin(), fr.end(), 0);
        for (int32_t i = 0; i < n; ++i) {
            fr[a[i] >> (pas << 3) & 0xff]++;
        }

        for (int32_t i = 1; i < 256; ++i) {
            fr[i] += fr[i - 1];
        }

        for (int32_t i = 0; i < n; ++i) {
            v[--fr[a[i] >> (pas << 3) & 0xff]] = a[i];
        }

        a = v;
    }

    std::vector<int32_t>().swap(v);
}

void radix_sort_base_65536(std::vector<int32_t>& a, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());

    if (n <= 1) {
        return;
    }

    std::vector<int32_t> fr(65536, 0), v(n);
    for (int32_t pas = 0; pas < 2; ++pas) {
        fill(fr.begin(), fr.end(), 0);
        for (int32_t i = 0; i < n; ++i) {
            fr[a[i] >> (pas << 4) & 0xffff]++;
        }

        for (int32_t i = 1; i < 65536; ++i) {
            fr[i] += fr[i - 1];
        }

        for (int32_t i = n - 1; i >= 0; --i) {
            v[--fr[a[i] >> (pas << 4) & 0xffff]] = a[i];
        }

        a = v;
    }

    std::vector<int32_t>().swap(v);
}