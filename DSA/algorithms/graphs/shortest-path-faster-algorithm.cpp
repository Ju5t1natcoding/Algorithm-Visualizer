#include "../../core/states.hpp"
#include <queue>

const int64_t INF = 2e18;

void spfa(std::vector<std::vector<std::pair<int32_t, int64_t>>>& g, int32_t s, std::vector<State>& states) { ///Shortest Path Faster Algorithm
    int32_t n = static_cast<int32_t>(g.size());
    std::vector<int64_t> dist(n, INF);
    std::vector<bool> in(n, false);
    std::queue<int32_t> q;
    dist[s] = 0;
    in[s] = true;
    q.push(s);

    while (!q.empty()) {
        int32_t x = q.front();
        q.pop();
        in[x] = false;

        for (auto& [y, c] : g[x]) {
            if (dist[x] + c < dist[y]) {
                dist[y] = dist[x] + c;

                if (!in[y]) {
                    q.push(y);
                    in[y] = true;
                }
            }
        }
    }
}