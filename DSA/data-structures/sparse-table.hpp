#pragma once
#include <cstdint>
#include <vector>

class SparseTable {
protected:
    int n, lgn; ///log2(n)
    std::vector<std::vector<int32_t>> st;

public:
    SparseTable(int32_t _n, std::vector<int32_t>& a);

    int32_t query(int32_t l, int32_t r);
};