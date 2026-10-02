#include "dsu.hpp"

DSU::DSU(int32_t n) {
    parent.resize(n);
    size.assign(n, 1);
    std::iota(parent.begin(), parent.end(), 0);
}

int32_t DSU::find(int32_t x) {
    return x == parent[x] ? x : parent[x] = find(parent[x]);
}

bool DSU::unite(int32_t a, int32_t b) {
    a = find(a);
    b = find(b);

    if (a == b) {
        return false;
    }

    if (size[a] < size[b]) {
        std::swap(a, b);
    }

    parent[b] = a;
    size[a] += size[b];
    return true;
}