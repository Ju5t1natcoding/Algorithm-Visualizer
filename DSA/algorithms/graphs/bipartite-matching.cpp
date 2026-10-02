#include "../../core/states.hpp"

void bipartite_matching(std::vector<std::vector<int32_t>>& g, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size());
    std::vector<int32_t> st(n, -1), dr(n, -1); ///left part and right part matchings
    std::vector<bool> viz(n, false);

    auto match = [&](auto&& match, int32_t x) -> bool {
        if (viz[x]) {
            return false;
        }

        viz[x] = true;
        for (int32_t y : g[x]) {
            if (dr[y] == -1) { ///we can directly match
                dr[y] = x;
                st[x] = y;
                return true;
            }
        }

        for (int32_t y : g[x]) {
            if (match(match, dr[y])) { ///if there is a better matching
                dr[y] = x;
                st[x] = y;
                return true;
            }
        }

        return false; ///there is no matching to take
    };

    bool ok = true;
    int32_t ans = 0; ///number of matchings

    while (ok) {
        ok = false;
        std::fill(viz.begin(), viz.end(), false);

        for (int i = 0; i < n; ++i) {
            if (st[i] == -1 && match(match, i)) {
                ok = true;
                ans++;
            }
        }
    }
}