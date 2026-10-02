#pragma once
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <string>

class Trie {
protected:
    struct TrieNode {
        std::unordered_map<unsigned char, int32_t> nxt;
        int32_t parent, pass, end;
        char pc; ///parent_char
        TrieNode(int32_t p = -1, char c = 0): parent(p), pc(c), pass(0), end(0) {
        }
    };

    std::vector<TrieNode> tr;

public:
    Trie();

    void insert(const std::string& s);
    int32_t walk(const std::string& s);
    bool search(const std::string& s);
    bool startsWith(const std::string& p);
    int32_t countPrefix(const std::string& p);
    bool erase(const std::string& s);
    void collect(int32_t v, std::string& curr, std::vector<std::string>& out);
    std::vector<std::string> autocomplete(const std::string& p);
};