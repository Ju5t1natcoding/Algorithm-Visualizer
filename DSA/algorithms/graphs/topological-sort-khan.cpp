#include "../../core/states.hpp"
#include <queue>

void topological_sort_khan(std::vector<std::vector<int32_t>>& g, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size());
    std::vector<int32_t> in(n, 0);

    for (int32_t i = 0; i < n; ++i) {
        for (int32_t x : g[i]) {
            in[x]++;
        }
    }

    std::queue<int32_t> q;
    for (int32_t i = 0; i < n; ++i) {
        if (!in[i]) {
            q.push(i);
        }
    }

    std::vector<int32_t> topo;

    while (!q.empty()) {
        int32_t x = q.front();
        q.pop();
        topo.push_back(x);

        for (int32_t y : g[x]) {
            in[y]--;

            if (!in[y]) {
                q.push(y);
            }
        }
    }
}