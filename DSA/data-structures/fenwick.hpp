#pragma once
#include <cstdint>
#include <vector>

class Fenwick {
private:
    int32_t n;
    std::vector<int64_t> f;

public:
    Fenwick(int32_t _n);

    void add(int32_t i, int64_t x);
    int64_t sum(int32_t i);
    int32_t kth(int64_t k);
};