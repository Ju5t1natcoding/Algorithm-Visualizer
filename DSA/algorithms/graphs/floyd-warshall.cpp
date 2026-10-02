#include "../../core/states.hpp"

const int64_t INF = 2e18;

void floyd_warshall(std::vector<std::vector<std::pair<int32_t, int64_t>>>& g, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size());
    std::vector<std::vector<int64_t>> dist(n, std::vector<int64_t>(n, INF));

    for (int32_t x = 0; x < n; ++x) {
        for (auto& [y, c] : g[x]) {
            dist[x][y] = c;
        }
    }

    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0; j < n; ++j) {
            for (int32_t k = 0; k < n; ++k) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}