#pragma once
#include <cstdint>
#include <vector>
#include <numeric>

class DSU {
protected:
    std::vector<int32_t> parent, size;

public:
    DSU(int32_t n);

    int32_t find(int32_t x);
    bool unite(int32_t a, int32_t b);
};