#include <cstdint>
#include <vector>

struct State {
    ///cod
};

void hld(std::vector<std::vector<std::pair<int32_t, int64_t>>>& g, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size());
    std::vector<int32_t> adc(n, 0), p(n, 0), heavy(n, 0), head(n, 0), dim(n, 0), poz(n, 0);
    int32_t curr = 0;

    auto dfs = [&](auto& dfs, int32_t x, int32_t par) -> void {
        p[x] = par;
        dim[x] = 1;
        int32_t mx = 0;

        for (auto& [y, c] : g[x]) {
            if (y == par) {
                continue;
            }

            adc[y] = adc[x] + 1;
            dfs(dfs, y, x);

            if (mx < dim[y]) {
                heavy[y] = x;
                mx = dim[y];
            }
        }
    };

    auto decomp = [&](auto& decomp, int x, int h) -> void {
        head[x] = h;
        poz[x] = ++curr;

        if (heavy[x]) {
            decomp(decomp, heavy[x], h);
        }

        for (auto& [y, c] : g[x]) {
            if (y == p[x] || y == heavy[x]) {
                continue;
            }

            decomp(decomp, y, y);
        }
    };

    dfs(dfs, 1, 0);
    decomp(decomp, 1, 0);
}

void centroid_decomposition(std::vector<std::vector<int32_t>>& g, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size());
    ///cod
}