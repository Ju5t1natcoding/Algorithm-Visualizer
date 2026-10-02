#include "../../core/states.hpp"

void tarjan_bridge_and_articulation_points(std::vector<std::vector<int32_t>>& g, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size());
    std::vector<int32_t> disc(n, -1), low(n, -1), art_points;
    std::vector<std::pair<int32_t, int32_t>> bridges;
    int32_t timp = 0;

    auto dfs = [&](auto&& dfs, int32_t x, int32_t p) -> void {
        disc[x] = low[x] = timp++;
        int32_t nrc = 0;

        for (int32_t y : g[x]) {
            if (y == p) {
                continue;
            }

            if (disc[y] != -1) {
                low[x] = std::min(low[x], disc[y]);
            } else {
                dfs(dfs, y, x);
                low[x] = std::min(low[x], low[y]);

                if (low[y] >= disc[x] && p != -1) { ///for articulation points
                    art_points.push_back(x);
                }

                if (low[y] > disc[x]) { ///for bridges
                    bridges.push_back(std::make_pair(std::min(x, y), std::max(x, y)));
                }
            }

            nrc++;
        }

        if (p == -1 && nrc > 1) { ///for articulation points
            art_points.push_back(x);
        }
    };

    for (int32_t i = 0; i < n; ++i) {
        if (disc[i] == -1) {
            dfs(dfs, i, -1);
        }
    }
}