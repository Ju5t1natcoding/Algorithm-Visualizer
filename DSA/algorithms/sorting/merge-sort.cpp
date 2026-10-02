#include "../../core/states.hpp"

void mergesort(std::vector<int32_t>& a, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    
    auto f = [&](auto&& f, int32_t st, int32_t dr, std::vector<int32_t>& a) {
        if (dr - st <= 1) {
            if (a[st - st] > a[dr - st]) {
                std::swap(a[st - st], a[dr - st]);
            }

            return;
        }

        int32_t n = static_cast<int32_t>(a.size());
        int32_t mij = st + ((dr - st) >> 1);
        std::vector<int32_t> l(a.begin(), a.begin() + mij), r(a.begin() + mij, a.end());
        f(f, st, mij, l);
        f(f, mij + 1, dr, r);
        std::vector<int32_t> v;
        int32_t i = 0, j = 0;

        while (i < mij && j < dr - st + 1 - mij) {
            if (l[i] <= r[j]) {
                v.push_back(l[i]);
                i++;
            } else {
                v.push_back(r[j]);
                j++;
            }
        }

        while (i < mij) {
            v.push_back(l[i]);
            i++;
        }

        std::vector<int32_t>().swap(l);

        while (j < dr - st + 1 - mij) {
            v.push_back(r[j]);
            j++;
        }

        std::vector<int32_t>().swap(r);
        a = v;
        std::vector<int32_t>().swap(v);
    };

    f(f, 0, n - 1, a);
}