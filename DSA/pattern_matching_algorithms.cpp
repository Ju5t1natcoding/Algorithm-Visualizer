#include <cstdint>
#include <vector>
#include <string>

struct State {
    ///cod
};

void naive(std::string& s, std::string& t, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(s.size()), m = static_cast<int32_t>(t.size());
    std::vector<int32_t> v;
    
    for (int32_t i = 0; i < n - m + 1; ++i) {
        int32_t j = 0;

        while (j < m && s[i + j] == t[j]) {
            j++;
        }

        if (j == m) {
            v.push_back(i);
        }
    }
}

void knuth_morris_pratt(std::string& s, std::string& t, std::vector<State>& states) { ///KMP
    int32_t n = static_cast<int32_t>(s.size()), m = static_cast<int32_t>(t.size());
    std::vector<int32_t> lps(m, 0), v;
    int32_t q = 0;
    lps[0] = 0;

    for (int i = 1; i < m; ++i) {
        while (q && t[i] != t[q]) {
            q = lps[q - 1];
        }

        if (t[i] == t[q]) {
            q++;
        }

        lps[i] = q;
    }

    for (int i = 0; i < n; ++i) {
        while (q && s[i] != t[q]) {
            q = lps[q - 1];
        }

        if (s[i] == t[q]) {
            q++;
        }

        if (q == m) {
            v.push_back(i - m + 1);
            q = lps[q - 1];
        }
    }
}

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
        return static_cast<int32_t>(1ll * a * b % mod);
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

void z_algorithm(std::string& s, std::string& t, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(s.size()), m = static_cast<int32_t>(t.size());
    std::vector<int32_t> z(n + m + 1, 0), v;
    std::string u = t + '$' + s;

    for (int32_t i = 1, l = 0, r = 0; i < static_cast<int32_t>(u.size()); ++i) {
        if (i <= r) {
            z[i] = std::min(r - i + 1, z[i - l]);
        }

        while (i + z[i] < static_cast<int32_t>(u.size()) && u[z[i]] == u[i + z[i]]) {
            z[i]++;
        }

        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (z[i + m + 1] == m) {
            v.push_back(i);
        }
    }
}