#include <cstdint>
#include <vector>
#include <queue>

struct State {
    ///cod
};

void bfs(std::vector<std::vector<int32_t>>& g, int32_t s, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size());
    std::queue<int32_t> q;
    std::vector<int32_t> dist(n, -1);
    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int32_t x = q.front();
        q.pop();

        for (int32_t y : g[x]) {
            if (dist[y] != -1) {
                continue;
            }

            dist[y] = dist[x] + 1;
            q.push(y);
        }
    }
}

void dfs(std::vector<std::vector<int32_t>>& g, int32_t s, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size());
    std::vector<int32_t> adc(n, -1);
    adc[s] = 0;

    auto f = [&](auto&& f, int32_t x) -> void {
        for (int32_t y : g[x]) {
            if (adc[y] != -1) {
                continue;
            }

            adc[y] = adc[x] + 1;
            f(f, y);
        }
    };

    f(f, s);
}

void dijkstra(std::vector<std::vector<std::pair<int32_t, int64_t>>>& g, int32_t s, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size());
    std::vector<int64_t> dist(n, -1);
    dist[s] = 0;
    std::priority_queue<std::pair<int64_t, int32_t>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [c, x] = pq.top();
        pq.pop();

        if (c != dist[x]) {
            continue;
        }

        for (auto& [y, q] : g[x]) {
            if (dist[y] == -1 || dist[y] > c + q) {
                dist[y] = c + q;
                pq.push({c + q, y});
            }
        }
    }
}

void bellman_ford(std::vector<std::vector<std::pair<int32_t, int64_t>>>& g, int32_t s, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size());
    ///cod
}

void A_sharp(std::vector<std::vector<std::pair<int32_t, int64_t>>>& g, int32_t s, std::vector<State>& states) { ///A*
    int32_t n = static_cast<int32_t>(g.size());
    ///cod
}