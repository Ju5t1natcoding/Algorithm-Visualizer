#include "../../core/states.hpp"
#include <queue>

const int8_t dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};

void dijkstra(std::vector<std::vector<int32_t>>& a, int32_t xs, int32_t ys, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size()), m = static_cast<int32_t>(a[0].size());
    std::vector<std::vector<int32_t>> dist(n, std::vector<int32_t>(m, -1));
    dist[xs][ys] = 0;
    std::priority_queue<std::pair<int32_t, std::pair<int32_t, int32_t>>> pq;
    pq.push(std::make_pair(0, std::make_pair(xs, ys)));

    auto inmat = [&](int32_t x, int32_t y) -> bool {
        return 0 <= x && x < n && 0 <= y && y < m;
    };

    while (!pq.empty()) {
        auto [c, p] = pq.top();
        pq.pop();
        auto [x, y] = p;

        if (c != dist[x][y]) {
            continue;
        }

        for (int k = 0; k < 4; ++k) {
            int32_t nx = x + dx[k], ny = y + dy[k];

            if (!inmat(nx, ny) || a[nx][ny] == -1 || dist[nx][ny] < c + 1) {
                continue;
            }

            dist[nx][ny] = c + 1;
            pq.push(std::make_pair(c + 1, std::make_pair(nx, ny)));
        }
    }
}