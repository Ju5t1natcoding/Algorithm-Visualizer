#pragma once
#include <cstdint>
#include <vector>

class SegmentTreeLazy {
protected:
    struct Node {
        int32_t lazy;
        int64_t val;
    };

    std::vector<Node> tr;

public:
    SegmentTreeLazy(int32_t _n);

    void build(int32_t nod, int32_t l, int32_t r, const std::vector<int32_t>& a);
    void push(int32_t nod, int32_t l, int32_t r);
    void update(int32_t nod, int32_t l, int32_t r, int32_t ul, int32_t ur, int32_t val);
    int64_t query(int32_t nod, int32_t l, int32_t r, int32_t ql, int32_t qr);
};