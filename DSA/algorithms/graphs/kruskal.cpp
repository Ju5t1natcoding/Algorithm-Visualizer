#include "../../core/states.hpp"
#include "../../data-structures/dsu.cpp"
#include <algorithm>

void kruskal(std::vector<std::vector<std::pair<int32_t, int64_t>>>& g, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size());
    std::vector<std::tuple<int32_t, int32_t, int64_t>> mch;

    for (int32_t i = 0; i < n; ++i) {
        for (auto& [x, c] : g[i]) {
            mch.push_back(std::make_tuple(std::min(i, x), std::max(i, x), c));
        }
    }

    std::sort(mch.begin(), mch.end(), [](const std::tuple<int32_t, int32_t, int64_t>& a, const std::tuple<int32_t, int32_t, int64_t>& b) {
        return std::get<2>(a) < std::get<2>(b);
    });
    mch.erase(std::unique(mch.begin(), mch.end()), mch.end());

    DSU dsu(n);
    int64_t cost = 0;
    std::vector<std::tuple<int32_t, int32_t, int64_t>> mst;

    for (auto& [x, y, c] : mch) {
        if (dsu.unite(x, y)) {
            cost += c;
            mst.push_back(std::make_tuple(x, y, c));

            if (mst.size() == static_cast<size_t>(n - 1)) {
                break;
            }
        }
    }
}