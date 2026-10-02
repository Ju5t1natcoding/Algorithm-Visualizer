#include "fenwick.hpp"

Fenwick::Fenwick(int32_t _n) {
    n = _n;
    f.assign(n + 1, 0);
}

void Fenwick::add(int32_t i, int64_t x) {
    for (; i <= n; i += i & -i) {
        f[i] += x;
    }
}

int64_t Fenwick::sum(int32_t i) {
    int64_t s = 0;
    for (; i; i -= i & -i) {
        s += f[i];
    }

    return s;
}

int32_t Fenwick::kth(int64_t k) {
    int32_t p = 0, pw = 1;

    while ((pw << 1) <= n) {
        pw <<= 1;
    }

    for (; pw; pw >>= 1) {
        int32_t nxt = p + pw;

        if (nxt <= n && f[nxt] < k) {
            p = nxt;
            k -= f[p];
        }
    }

    return p + 1;
}