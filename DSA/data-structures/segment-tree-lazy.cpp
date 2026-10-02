#include "segment-tree-lazy.hpp"

SegmentTreeLazy::SegmentTreeLazy(int32_t _n) {
    tr.assign(4 * _n + 5, Node());
}

void SegmentTreeLazy::build(int32_t nod, int32_t l, int32_t r, const std::vector<int32_t>& a) {
    if (l == r) {
        tr[nod].val = a[l];
        return;
    }

    int32_t mij = l + ((r - l) >> 1);
    build(nod << 1, l, mij, a);
    build(nod << 1 | 1, mij + 1, r, a);
    tr[nod].val = tr[nod << 1].val + tr[nod << 1 | 1].val;
}

void SegmentTreeLazy::push(int32_t nod, int32_t l, int32_t r) {
    if (l == r) {
        return;
    }

    int32_t mij = l + ((r - l) >> 1);
    tr[nod << 1].val = static_cast<int64_t>(tr[nod].lazy) * (mij - l + 1);
    tr[nod << 1].lazy = tr[nod].lazy;
    tr[nod << 1 | 1].val = static_cast<int64_t>(tr[nod].lazy) * (r - mij);
    tr[nod << 1 | 1].lazy = tr[nod].lazy;
    tr[nod].lazy = 0;
}

void SegmentTreeLazy::update(int32_t nod, int32_t l, int32_t r, int32_t ul, int32_t ur, int32_t val) {
    if (ul > ur || ur < l || r < ul) {
        return;
    }

    if (ul <= l && r <= ur) {
        tr[nod].val = static_cast<int64_t>(val) * (r - l + 1);
        tr[nod].lazy = val;
        return;
    }

    push(nod, l, r);
    int32_t mij = l + ((r - l) >> 1);
    update(nod << 1, l, mij, ul, ur, val);
    update(nod << 1 | 1, mij + 1, r, ul, ur, val);
    tr[nod].val = tr[nod << 1].val + tr[nod << 1 | 1].val;
}

int64_t SegmentTreeLazy::query(int32_t nod, int32_t l, int32_t r, int32_t ql, int32_t qr) {
    if (ql > qr || qr < l || r < ql) {
        return 0;
    }

    if (ql <= l && r <= qr) {
        return tr[nod].val;
    }

    push(nod, l, r);
    int32_t mij = l + ((r - l) >> 1);

    if (qr <= mij) {
        return query(nod << 1, l, mij, ql, qr);
    }

    if (mij < ql) {
        return query(nod << 1 | 1, mij + 1, r, ql, qr);
    }

    return query(nod << 1, l, mij, ql, qr) + query(nod << 1 | 1, mij + 1, r, ql, qr);
}