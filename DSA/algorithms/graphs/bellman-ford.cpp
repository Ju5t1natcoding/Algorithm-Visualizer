#include "../../core/states.hpp"

const int64_t INF = 2e18;

void bellman_ford(std::vector<std::vector<std::pair<int32_t, int64_t>>>& g, int32_t s, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size());
    std::vector<std::tuple<int32_t, int32_t, int64_t>> mch;
    std::vector<int64_t> dist(n, INF);
    dist[s] = 0;

    for (int32_t x = 0; x < n; ++x) {
        for (auto& [y, c] : g[x]) {
            mch.push_back(std::make_tuple(x, y, c));
        }
    }

    bool infinite_cycle = false;
    for (int32_t i = 1; i <= n; ++i) {
        for (auto& [x, y, c] : mch) {
            if (dist[x] != INF && dist[x] + c < dist[y]) {
                if (i == n) {
                    infinite_cycle = true;
                    break;
                }

                dist[y] = dist[x] + c;
            }
        }
    }
}