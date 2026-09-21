#include <cstdint>
#include <vector>
#include <queue>

struct State {
    ///cod
};

const int8_t dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
const int32_t INF = 1e9;

void lee(std::vector<std::vector<int32_t>>& a, int32_t xs, int32_t ys, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size()), m = static_cast<int32_t>(a[0].size());
    std::queue<std::pair<int32_t, int32_t>> q;
    q.push(std::make_pair(xs, ys));
    std::vector<std::vector<int32_t>> dist(n, std::vector<int32_t>(m, -1));
    dist[xs][ys] = 0;

    auto inmat = [&](int32_t x, int32_t y) -> bool {
        return 0 <= x && x < n && 0 <= y && y < m;
    };

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (int8_t k = 0; k < 4; ++k) {
            int32_t nx = x + dx[k], ny = y + dy[k];

            if (!inmat(nx, ny) || a[nx][ny] == -1 || dist[nx][ny] != -1) {
                continue;
            }

            dist[nx][ny] = dist[x][y] + 1;
            q.push(std::make_pair(nx, ny));
        }
    }
}

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

void A_sharp(std::vector<std::vector<int32_t>>& a, int32_t xs, int32_t ys, int32_t xf, int32_t yf, std::vector<State>& states) { ///A*
    int32_t n = static_cast<int32_t>(a.size()), m = static_cast<int32_t>(a[0].size());

    struct nod {
        int32_t i, j, f, g;

        nod(int32_t i, int32_t j, int32_t f, int32_t g): i(i), j(j), f(f), g(g) {
        }

        bool operator>(const nod& o) const {
            if (f != o.f) {
                return f < o.f;
            }

            return g < o.g;
        }
    };

    auto manhattan = [](int32_t i, int32_t j, int32_t x, int32_t y) -> int {
        return abs(i - x) + abs(j - y);
    };

    auto inmat = [&](int32_t x, int32_t y) {
        return 0 <= x && x < n && 0 <= y && y < m;
    };

    std::vector<std::vector<int32_t>> g_score(n, std::vector<int32_t>(m, INF));
    std::vector<std::vector<std::pair<int32_t, int32_t>>> p(n, std::vector<std::pair<int32_t, int32_t>>(m, std::make_pair(-1, -1)));
    std::priority_queue<nod, std::vector<nod>, std::greater<nod>> pq;
    g_score[xs][ys] = 0;
    int32_t hs = manhattan(xs, ys, xf, yf);
    pq.push(nod(xs, ys, hs, 0));

    while (!pq.empty()) {
        auto [x, y, f, g] = pq.top();
        pq.pop();

        if (x == xf && y == yf) {
            ///path reconstruction
            return;
        }

        if (g > g_score[x][y]) {
            continue;
        }

        for (int8_t k = 0; k < 4; ++k) {
            int32_t nx = x + dx[k], ny = y + dy[k];

            if (!inmat(nx, ny) || a[nx][ny] == -1) {
                continue;
            }

            int32_t ng = g + 1;

            if (ng < g_score[nx][ny]) {
                g_score[nx][ny] = ng;
                p[nx][ny] = std::make_pair(x, y);
                int32_t h = manhattan(nx, ny, xf, yf), nf = ng + h;
                pq.push({nx, ny, nf, ng});
            }
        }
    }
}