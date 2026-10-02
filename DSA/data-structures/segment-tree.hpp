#pragma once
#include <cstdint>
#include <vector>

class SegmentTree {
protected:
    std::vector<int64_t> tr;

public:
    SegmentTree(int32_t _n);

    void build(int32_t nod, int32_t l, int32_t r, const std::vector<int32_t>& a);
    void update(int32_t nod, int32_t l, int32_t r, int32_t pos, int32_t val);
    int64_t query(int32_t nod, int32_t l, int32_t r, int32_t ql, int32_t qr);
};