#include "../../core/states.hpp"
#include <random>
#include <chrono>

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

void quicksort(std::vector<int32_t>& a, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    
    auto f = [&](auto&& f, int32_t st, int32_t dr, std::vector<int32_t>& a) {
        if (st == dr) {
            return;
        }
        
        int32_t p = rng() % (dr - st + 1) + st;
        std::vector<int32_t> l, r;

        for (int32_t i = st; i <= dr; ++i) {
            if (i == p) {
                continue;
            }

            if (a[i] < a[p]) {
                l.push_back(a[i]);
            } else if (a[i] > a[p]) {
                r.push_back(a[i]);
            } else { ///for equal distribution
                if (l.size() <= r.size()) {
                    l.push_back(a[i]);
                } else {
                    r.push_back(a[i]);
                }
            }
        }

        f(f, st, p - 1, l);
        f(f, p + 1, dr, r);
    };

    f(f, 0, n - 1, a);
}