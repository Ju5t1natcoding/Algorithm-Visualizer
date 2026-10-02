#pragma once
#include <cstdint>
#include <vector>
#include <array>

class BinaryTrie {
protected:
    struct TrieNode {
        std::array<int32_t, 2> nxt;
        int32_t parent, pass, end;
        bool p_val; ///parent_value

        TrieNode(int32_t p = -1, bool v = false): parent(p), p_val(v), pass(0), end(0) {
            nxt.fill(-1);
        }
    };

    std::vector<TrieNode> tr;

public:
    BinaryTrie();

    void insert(int32_t x);
    int32_t walk(int32_t x);
    bool erase(int32_t x);
    bool search(int32_t x);
    int32_t max_xor(int32_t x);
    int32_t min_xor(int32_t x);
    int32_t countLess(int32_t x);
    int32_t kth(int32_t k);
    int32_t countXorLess(int32_t x, int32_t k);
};