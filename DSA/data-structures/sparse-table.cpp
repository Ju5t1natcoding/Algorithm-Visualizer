#include "sparse-table.hpp"

SparseTable::SparseTable(int32_t _n, std::vector<int32_t>& a) {
    n = _n;
    lgn = 0;

    while ((1 << lgn) <= n) {
        lgn++;
    }

    st.assign(lgn, std::vector<int32_t>(n, 0));
    for (int32_t i = 0; i < n; ++i) {
        st[0][i] = a[i];
    }

    for (int32_t k = 1; k < lgn; ++k) {
        for (int32_t i = 0; i + (1 << k) <= n; ++i) {
            st[k][i] = std::min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
        }
    }
}

int32_t SparseTable::query(int32_t l, int32_t r) {
    int32_t len = r - l + 1, k = log2(len);
    return std::min(st[k][l], st[k][r - (1 << k) + 1]);
}