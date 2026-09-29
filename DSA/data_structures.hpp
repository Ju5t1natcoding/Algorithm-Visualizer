#pragma once
#include <cstdint>
#include <vector>
#include <numeric>
#include <array>
#include <string>

class DSU {
    std::vector<int32_t> parent, size;

public:
    DSU(int n): parent(n), size(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int32_t find(int32_t x) {
        return x == parent[x] ? x : parent[x] = find(parent[x]);
    }

    bool unite(int32_t a, int32_t b) {
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
};

class Heap {
    ///cod
};

class Sparse_Table {
    ///cod
};

class Fenwick_Tree {
    ///cod
};

class Segment_Tree {
    ///cod
};

class Lazy_Segment_Tree {
    ///cod
};

class Persistent_Segment_Tree {
    ///cod
};

struct TrieNode {
    std::array<int32_t, 26> nxt;
    bool terminal_node;
};

class Trie {
protected:
    std::vector<TrieNode> trie;

public:
    Trie() {
    }
};

class Trie_binary {
    ///cod
};

class Treap {
    ///cod
};

class Splay_Tree {
    ///cod
};