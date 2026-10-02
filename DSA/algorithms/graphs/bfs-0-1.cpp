#include "../../core/states.hpp"
#include <deque>

void bfs_0_1(std::vector<std::vector<std::pair<int32_t, int8_t>>>& g, int32_t s, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size());
    std::deque<int32_t> dq;
    std::vector<int32_t> dist(n, -1);
    std::vector<bool> viz(n, false);
    dist[s] = 0;
    viz[s] = true;
    dq.push_back(s);

    while (!dq.empty()) {
        int32_t x = dq.front();
        dq.pop_front();

        if (viz[x]) {
            continue;
        }

        viz[x] = true;
        for (auto& [y, c] : g[x]) {
            if (dist[y] != -1 && dist[y] <= dist[x] + c) {
                continue;
            }

            dist[y] = dist[x] + c;

            if (!c) {
                dq.push_front(y);
            } else {
                dq.push_back(y);
            }
        }
    }
}