#include "../../core/states.hpp"

void rabin_karp(std::string& s, std::string& t, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(s.size()), m = static_cast<int32_t>(t.size());
    int32_t base = 131, mod = 1e9 + 7;

    auto addm = [&](int32_t a, int32_t b) -> int32_t {
        a += b;

        if (a >= mod) {
            a -= mod;
        }

        return a;
    };

    auto prodm = [&](int32_t a, int32_t b) -> int32_t {
        return static_cast<int32_t>(static_cast<int64_t>(a) * b % mod);
    };

    std::vector<int32_t> h(n + 1, 0), p(n + 1, 1), v;
    for (int i = 1; i <= n; ++i) {
        p[i] = prodm(p[i - 1], base);
        h[i] = addm(prodm(h[i - 1], base), s[i - 1]);
    }

    int32_t hsh = 0;
    for (int i = 0; i < m; ++i) {
        hsh = addm(prodm(hsh, base), t[i]);
    }

    for (int i = 0; i <= n - m; ++i) {
        int32_t hsh_i = addm(h[i + m], mod - prodm(h[i], p[m]));

        if (hsh_i == hsh) {
            v.push_back(i);
        }
    }
}