#include "../../core/states.hpp"

void tarjan_scc(std::vector<std::vector<int32_t>>& g, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size()), timp = 0;
    std::vector<int32_t> disc(n, -1), low(n, -1), st;
    std::vector<int32_t> in(n, false);
    std::vector<std::vector<int32_t>> comp;

    auto dfs = [&](auto&& dfs, int x) -> void {
        disc[x] = low[x] = timp++;
        st.push_back(x);
        in[x] = true;

        for (int32_t y : g[x]) {
            if (disc[y] == -1) {
                dfs(dfs, y);
                low[x] = std::min(low[x], low[y]);
            } else if (in[y]) {
                low[x] = std::min(low[x], disc[y]);
            }
        }

        if (disc[x] == low[x]) {
            comp.emplace_back();

            while (st.back() != x) {
                comp.back().push_back(st.back());
                in[st.back()] = false;
                st.pop_back();
            }

            comp.back().push_back(x);
            in[x] = false;
            st.pop_back();
        }
    };

    for (int32_t i = 0; i < n; ++i) {
        if (disc[i] == -1) {
            dfs(dfs, i);
        }
    }
}