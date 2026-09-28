#include "data_structures.hpp"
#include <queue>
#include <algorithm>

struct State {
    ///cod
};

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

void kruskal(std::vector<std::vector<std::pair<int32_t, int64_t>>>& g, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size());
    std::vector<std::tuple<int32_t, int32_t, int64_t>> mch;

    for (int32_t i = 0; i < n; ++i) {
        for (auto& [x, c] : g[i]) {
            mch.push_back(std::make_tuple(std::min(i, x), std::max(i, x), c));
        }
    }

    std::sort(mch.begin(), mch.end(), [](const std::tuple<int32_t, int32_t, int64_t>& a, const std::tuple<int32_t, int32_t, int64_t>& b) {
        return std::get<2>(a) < std::get<2>(b);
    });
    mch.erase(std::unique(mch.begin(), mch.end()), mch.end());

    DSU dsu(n);
    int64_t cost = 0;
    std::vector<std::tuple<int32_t, int32_t, int64_t>> mst;

    for (auto& [x, y, c] : mch) {
        if (dsu.unite(x, y)) {
            cost += c;
            mst.push_back(std::make_tuple(x, y, c));

            if (mst.size() == static_cast<size_t>(n - 1)) {
                break;
            }
        }
    }
}

void prim(std::vector<std::vector<std::pair<int32_t, int64_t>>>& g, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size());
    ///cod
}

void bipartite_matching(std::vector<std::vector<int32_t>>& g, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size());
    ///cod
}

void eulerian_paths(std::vector<std::vector<int32_t>>& g, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size());
    ///cod
}

void eulerian_cycles(std::vector<std::vector<int32_t>>& g, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size());
    ///cod
}

void havel_hakimi(std::vector<int32_t>& deg, std::vector<State>& states) { ///test if a graph is valid based on the degrees of the nodes
    int32_t n = static_cast<int32_t>(deg.size());
    std::sort(deg.begin(), deg.end(), std::greater<int32_t>());
    bool ok = true;

    while (deg[0] > 0) {
        if (deg[0] >= n) {
            ///cod
            ok = false;
            break;
        }

        for (int i = 1; i <= deg[0]; ++i) {
            deg[i]--;

            if (deg[i] < 0) {
                ok = false;
                break;
            }
        }

        if (!ok) {
            ///cod
            break;
        }

        sort(deg.begin(), deg.end(), std::greater<int32_t>());
    }
}