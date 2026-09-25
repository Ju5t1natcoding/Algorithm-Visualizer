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
            dim[x] += dim[y];

            if (mx < dim[y]) {
                heavy[x] = y;
                mx = dim[y];
            }
        }
    };

    auto decomp = [&](auto& decomp, int32_t x, int32_t h) -> void {
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

void centroid_decomposition(std::vector<std::vector<std::pair<int32_t, int64_t>>>& g, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size());
    std::vector<int32_t> sz(n, 0), parent(n, -1), centroid_parent(n, -1);
    std::vector<bool> marked(n, false);

    auto dim = [&](auto&& dim, int32_t x, int32_t p) -> int32_t {
        sz[x] = 1;
        for (auto& [y, c] : g[x]) {
            if (y == p || marked[y]) {
                continue;
            }

            sz[x] += dim(dim, y, x);
        }

        return sz[x];
    };

    auto get_centroid = [&](auto&& get_centroid, int32_t x, int32_t p, int32_t nr) -> int32_t {
        for (auto& [y, c] : g[x]) {
            if (y == p || marked[y]) {
                continue;
            }

            if (sz[y] > (nr >> 1)) {
                return get_centroid(get_centroid, y, x, nr);
            }
        }

        return x;
    };

    auto decomp = [&](auto&& decomp, int32_t x, int32_t p) -> void {
        int32_t nr = dim(dim, x, -1);
        int32_t c = get_centroid(get_centroid, x, -1, nr);
        centroid_parent[c] = p;
        marked[c] = true;

        for (auto& [y, _] : g[c]) {
            if (marked[y]) {
                continue;
            }

            decomp(decomp, y, c);
        }
    };

    decomp(decomp, 1, -1);
}