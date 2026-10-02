#include "../../core/states.hpp"

void eulerian_paths_cycles(std::vector<std::vector<int32_t>>& g, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size());
    std::vector<bool> viz(n, false);
    int32_t start = -1;

    for (int i = 0; i < n; ++i) {
        if (static_cast<int32_t>(g[i].size())) {
            start = i;
            break;
        }
    }

    if (start == -1) { ///trivial eulerian graph
        return;
    }

    auto dfs = [&](auto&& dfs, int32_t x) -> void {
        for (int y : g[x]) {
            if (viz[y]) {
                continue;
            }

            viz[y] = true;
            dfs(dfs, y);
        }
    };

    viz[start] = true;
    dfs(dfs, start);

    for (int i = 0; i < n; ++i) {
        if (!viz[i] && static_cast<int32_t>(g[i].size())) { ///not a connected graph, therefore impossible for it to be eulerian
            return;
        }
    }

    int32_t nr_odd = 0;
    for (int i = 0; i < n; ++i) {
        nr_odd += static_cast<int32_t>(g[i].size()) & 1;
    }

    if (!nr_odd) { ///eulerian cycle
        return;
    } else if (nr_odd == 2) { ///eulerian path
        return;
    } else { ///not eulerian graph
        return;
    }
}