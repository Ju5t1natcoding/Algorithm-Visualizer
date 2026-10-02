#include "segment-tree.hpp"

SegmentTree::SegmentTree(int32_t _n) {
    tr.assign(4 * _n + 5, 0);
}

void SegmentTree::build(int32_t nod, int32_t l, int32_t r, const std::vector<int32_t>& a) {
    if (l == r) {
        tr[nod] = a[l];
        return;
    }

    int32_t mij = l + ((r - l) >> 1);
    build(nod << 1, l, mij, a);
    build(nod << 1 | 1, mij + 1, r, a);
    tr[nod] = tr[nod << 1] + tr[nod << 1 | 1];
}

void SegmentTree::update(int32_t nod, int32_t l, int32_t r, int32_t pos, int32_t val) {
    if (l == r) {
        tr[nod] = val;
        return;
    }

    int32_t mij = l + ((r - l) >> 1);

    if (pos <= mij) {
        update(nod << 1, l, mij, pos, val);
    } else {
        update(nod << 1 | 1, mij + 1, r, pos, val);
    }

    tr[nod] = tr[nod << 1] + tr[nod << 1 | 1];
}

int64_t SegmentTree::query(int32_t nod, int32_t l, int32_t r, int32_t ql, int32_t qr) {
    if (ql > qr || qr < l || r < ql) {
        return 0;
    }

    if (ql <= l && r <= qr) {
        return tr[nod];
    }

    int32_t mij = l + ((r - l) >> 1);

    if (qr <= mij) {
        return query(nod << 1, l, mij, ql, qr);
    }

    if (mij < ql) {
        return query(nod << 1 | 1, mij + 1, r, ql, qr);
    }

    return query(nod << 1, l, mij, ql, qr), query(nod << 1 | 1, mij + 1, r, ql, qr);
}