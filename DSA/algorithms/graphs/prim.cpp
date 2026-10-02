#include "../../core/states.hpp"
#include <queue>

void prim(std::vector<std::vector<std::pair<int32_t, int64_t>>>& g, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size());
    std::priority_queue<std::tuple<int32_t, int32_t, int32_t>, std::vector<std::tuple<int32_t, int32_t, int32_t>>, std::greater<std::tuple<int32_t, int32_t, int32_t>>> pq;
    std::vector<bool> viz(n, false);
    std::vector<int32_t> parent(n, -1);
    int64_t ans = 0;
    pq.push(std::make_tuple(0, 0, -1));

    while (!pq.empty()) {
        auto [c, x, p] = pq.top();
        pq.pop();

        if (viz[x]) {
            continue;
        }

        parent[x] = p;
        ans += c;
        viz[x] = true;

        for (auto& [y, c] : g[x]) {
            if (viz[y]) {
                continue;
            }

            pq.push({c, y, x});
        }
    }
}