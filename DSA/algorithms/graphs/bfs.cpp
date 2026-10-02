#include "../../core/states.hpp"
#include <queue>

void bfs(std::vector<std::vector<int32_t>>& g, int32_t s, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size());
    std::queue<int32_t> q;
    std::vector<int32_t> dist(n, -1);
    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int32_t x = q.front();
        q.pop();

        for (int32_t y : g[x]) {
            if (dist[y] != -1) {
                continue;
            }

            dist[y] = dist[x] + 1;
            q.push(y);
        }
    }
}