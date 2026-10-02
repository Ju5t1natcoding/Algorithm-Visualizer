#pragma once
#include <cstdint>
#include <vector>
#include <variant>
#include <string>
#include <utility>

struct ArrayState {
    ///cod
};

struct GraphState {
    ///cod
};

struct TreeState {
    ///cod
};

struct GridState {
    ///cod
};

struct StringState {
    ///cod
};

struct TrieState {
    std::vector<std::vector<std::pair<unsigned char, int32_t>>> edges; ///edges[x] sorted by character
    std::vector<int32_t> end, fail, dict; ///how many words end in node |\/| -1 = not calculated/root |\/| -1 = does not exist
    std::vector<std::pair<int32_t, int32_t>> matches; ///std::make_pair(position of end of text, index of pattern)
    int32_t curr = -1, other = -1, pos = -1; ///marked principal node |\/| secondary node (fail target, y candidate etc.) |\/| current position in text, -1 if it's not the case
    std::string note;
};

using State = std::variant<ArrayState, GraphState, TreeState, GridState, StringState, TrieState>;