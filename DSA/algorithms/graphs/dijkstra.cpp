#include "../../core/states.hpp"
#include <queue>

void dijkstra(std::vector<std::vector<std::pair<int32_t, int64_t>>>& g, int32_t s, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size());
    std::vector<int64_t> dist(n, -1);
    dist[s] = 0;
    std::priority_queue<std::pair<int64_t, int32_t>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [c, x] = pq.top();
        pq.pop();

        if (c != dist[x]) {
            continue;
        }

        for (auto& [y, q] : g[x]) {
            if (dist[y] == -1 || dist[y] > c + q) {
                dist[y] = c + q;
                pq.push({c + q, y});
            }
        }
    }
}