#include "../../core/states.hpp"
#include <unordered_set>

const int64_t INF = 2e18;

void dial(std::vector<std::vector<std::pair<int32_t, int32_t>>>& g, int32_t s, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size()),  mx = 0; ///max weight on edge

    for (int32_t x = 0; x < n; ++x) {
        for (auto& [y, c] : g[x]) {
            mx = std::max(mx, c);
        }
    }

    std::vector<int32_t> dist(n, INF);
    dist[s] = 0;
    int32_t mx_dist = mx * (n - 1);
    std::vector<std::unordered_set<int32_t>> bkts(mx_dist + 1);
    bkts[0].insert(s);

    for (int32_t d = 0; d <= mx; ++d) {
        while (!bkts[d].empty()) {
            int32_t x = *bkts[d].begin();
            bkts[d].erase(bkts[d].begin());

            if (d > dist[x]) {
                continue;
            }

            for (auto& [y, c] : g[x]) {
                if (d + c < dist[y]) {
                    if (dist[y] != INF) {
                        bkts[dist[y]].erase(y);
                    }

                    dist[y] = d + c;
                    bkts[d + c].insert(y);
                }
            }
        }
    }
}