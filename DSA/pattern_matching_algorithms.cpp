#include <cstdint>
#include <vector>
#include <string>

struct State {
    ///cod
};

void naive(std::string& s, std::string& t, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(s.size()), m = static_cast<int32_t>(t.size());
    std::vector<int32_t> v;
    
    for (int32_t i = 0; i < n - m + 1; ++i) {
        int32_t j = 0;

        while (j < m && s[i + j] == t[j]) {
            j++;
        }

        if (j == m) {
            v.push_back(i);
        }
    }
}

void knuth_morris_pratt(std::string& s, std::string& t, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(s.size()), m = static_cast<int32_t>(t.size());
    ///cod
}

void rabin_karp(std::string& s, std::string& t, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(s.size()), m = static_cast<int32_t>(t.size());
    ///cod
}

void z_algorithm(std::string& s, std::string& t, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(s.size()), m = static_cast<int32_t>(t.size());
    ///cod
}

void aho_corasick(std::string& s, std::string& t, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(s.size()), m = static_cast<int32_t>(t.size());
    ///cod
}