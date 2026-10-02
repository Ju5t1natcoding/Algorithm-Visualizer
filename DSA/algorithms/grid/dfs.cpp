#include "../../core/states.hpp"

const int8_t dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};

void dfs(std::vector<std::vector<int32_t>>& a, int32_t xs, int32_t ys, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size()), m = static_cast<int32_t>(a[0].size());
    std::vector<std::vector<int32_t>> dist(n, std::vector<int32_t>(m, -1));

    auto inmat = [&](int32_t x, int32_t y) -> bool {
        return 0 <= x && x < n && 0 <= y && y < m;
    };

    auto f = [&](auto&& f, int32_t x, int32_t y)  -> void {
        for (int8_t k = 0; k < 4; ++k) {
            int32_t nx = x + dx[k], ny = y + dy[k];

            if (!inmat(nx, ny) || a[nx][ny] == -1 || dist[nx][ny] != -1) {
                continue;
            }

            dist[nx][ny] = dist[x][y] + 1;
            f(f, nx, ny);
        }
    };

    f(f, xs, ys);
}