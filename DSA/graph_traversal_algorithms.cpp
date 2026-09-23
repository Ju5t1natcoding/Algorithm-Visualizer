#include <cstdint>
#include <vector>
#include <queue>
#include <deque>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <sstream>

struct State {
    ///cod
};

const int64_t INF = 1e18;

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

void bfs_0_1(std::vector<std::vector<std::pair<int32_t, int8_t>>>& g, int32_t s, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size());
    std::deque<int32_t> dq;
    std::vector<int32_t> dist(n, -1);
    std::vector<bool> viz(n, false);
    dist[s] = 0;
    viz[s] = true;
    dq.push_back(s);

    while (!dq.empty()) {
        int32_t x = dq.front();
        dq.pop_front();

        if (viz[x]) {
            continue;
        }

        viz[x] = true;
        for (auto& [y, c] : g[x]) {
            if (dist[y] != -1 && dist[y] <= dist[x] + c) {
                continue;
            }

            dist[y] = dist[x] + c;

            if (!c) {
                dq.push_front(y);
            } else {
                dq.push_back(y);
            }
        }
    }
}

void floyd_warshall(std::vector<std::vector<std::pair<int32_t, int64_t>>>& g, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size());
    std::vector<std::vector<int64_t>> dist(n, std::vector<int64_t>(n, INF));

    for (int32_t x = 0; x < n; ++x) {
        for (auto& [y, c] : g[x]) {
            dist[x][y] = c;
        }
    }

    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0; j < n; ++j) {
            for (int32_t k = 0; k < n; ++k) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
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
    std::vector<std::tuple<int32_t, int32_t, int64_t>> mch;
    std::vector<int64_t> dist(n, INF);
    dist[s] = 0;

    for (int32_t x = 0; x < n; ++x) {
        for (auto& [y, c] : g[x]) {
            mch.push_back(std::make_tuple(x, y, c));
        }
    }

    bool infinite_cycle = false;
    for (int32_t i = 1; i <= n; ++i) {
        for (auto& [x, y, c] : mch) {
            if (dist[x] != INF && dist[x] + c < dist[y]) {
                if (i == n) {
                    infinite_cycle = true;
                    break;
                }

                dist[y] = dist[x] + c;
            }
        }
    }
}

void dial(std::vector<std::vector<std::pair<int32_t, int32_t>>>& g, int32_t s, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size()),  mx = 0; ///max weight on edge

    for (int32_t x = 0; x < n; ++x) {
        for (auto& [y, c] : g[x]) {
            mx = std::max(mx, c);
        }
    }

    std::vector<int32_t> dist(n, INF);
    dist[s] = 0;
    int32_t mx_dist = mx * (n - 1);
    std::vector<std::unordered_set<int32_t>> bkts(mx_dist + 1);
    bkts[0].insert(s);

    for (int32_t d = 0; d <= mx; ++d) {
        while (!bkts[d].empty()) {
            int32_t x = *bkts[d].begin();
            bkts[d].erase(bkts[d].begin());

            if (d > dist[x]) {
                continue;
            }

            for (auto& [y, c] : g[x]) {
                if (d + c < dist[y]) {
                    if (dist[y] != INF) {
                        bkts[dist[y]].erase(y);
                    }

                    dist[y] = d + c;
                    bkts[d + c].insert(y);
                }
            }
        }
    }
}

void spfa(std::vector<std::vector<std::pair<int32_t, int64_t>>>& g, int32_t s, std::vector<State>& states) { ///Shortest Path Faster Algorithm
    int32_t n = static_cast<int32_t>(g.size());
    std::vector<int64_t> dist(n, INF);
    std::vector<bool> in(n, false);
    std::queue<int32_t> q;
    dist[s] = 0;
    in[s] = true;
    q.push(s);

    while (!q.empty()) {
        int32_t x = q.front();
        q.pop();
        in[x] = false;

        for (auto& [y, c] : g[x]) {
            if (dist[x] + c < dist[y]) {
                dist[y] = dist[x] + c;

                if (!in[y]) {
                    q.push(y);
                    in[y] = true;
                }
            }
        }
    }
}

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

void two_SAT(std::string& s, std::vector<State>& states) {
    struct term {
        int32_t id;
        bool neg;

        int32_t get_node() {
            return neg ? (id << 1 | 1) : (id << 1);
        }
    };

    auto neg = [](int32_t x) -> int32_t {
        return x ^ 1;
    };

    auto to_upper = [](std::string s) -> std::string {
        std::transform(s.begin(), s.end(), s.begin(), [](char c) { return std::toupper(c); });
        return s;
    };

    std::unordered_map<std::string, int32_t> var2id;

    auto get_var_id = [&](const std::string& s) -> int32_t {
        if (var2id.find(s) == var2id.end()) {
            var2id[s] = static_cast<int32_t>(var2id.size());
        }

        return var2id[s];
    };

    std::string formula = s;
    for (char& c : formula) {
        if (c == '(' || c == ')' || c == ',' || c == '^') {
            c = ' ';
        }
    }

    std::string uformula = to_upper(formula);
    std::stringstream ss(uformula);
    std::string token;
    std::vector<std::string> clause_string;
    std::string curr = "";

    while (ss >> token) {
        if (token == "AND" || token == "&&") {
            if (!curr.empty()) {
                clause_string.push_back(curr);
                curr = "";
            }
        } else {
            curr += token + " ";
        }
    }

    if (!curr.empty()) {
        clause_string.push_back(curr);
    }

    struct raw_clause {
        term t1, t2;
        bool single; ///only has one term
    };

    std::vector<raw_clause> parsed_clauses;
    for (const std::string& c_str : clause_string) {
        std::stringstream css(c_str);
        std::vector<std::string> cuv;
        std::string w;

        while (css >> w) {
            cuv.push_back(w);
        }

        if (cuv.empty()) {
            continue;
        }

        std::vector<term> terms;
        for (size_t i = 0; i < cuv.size(); ++i) {
            if (cuv[i] == "OR" || cuv[i] == "||") {
                continue;
            }

            bool is_neg = false;

            while (i < cuv.size() && cuv[i] == "NOT" || cuv[i] == "||") {
                is_neg = true;
                i++;
            }
            
            if (cuv[i].rfind("NOT_", 0) == 0 || cuv[i].rfind("!", 0) == 0) {
                is_neg = true;
                cuv[i] = cuv[i].substr(cuv[i].find_first_not_of("NOT_!"));
            }

            if (cuv.empty()) {
                continue;
            }

            int32_t id = get_var_id(cuv[i]);
            terms.push_back({id, is_neg});
        }

        if (terms.size() == 1) {
            parsed_clauses.push_back({terms[0], terms[0], true});
        } else if (terms.size() >= 2) {
            parsed_clauses.push_back({terms[0], terms[1], false});
        }
    }

    int32_t num_var = static_cast<int32_t>(var2id.size());
    int32_t num_nodes = num_var << 1;
    std::vector<std::vector<int32_t>> g(num_nodes);

    for (auto& clause : parsed_clauses) {
        int32_t x = clause.t1.get_node();

        if (clause.single) {
            g[neg(x)].push_back(x);
        } else {
            int32_t y = clause.t2.get_node();
            g[neg(x)].push_back(y);
            g[neg(y)].push_back(x);
        }
    }

    std::vector<int32_t> disc(num_nodes, -1), low(num_nodes, -1), st, scc_id(num_nodes, -1);
    std::vector<bool> in(num_nodes, false);
    int32_t timp = 0, scc_counter = 0;

    auto tarjan_dfs = [&](auto&& self, int32_t x) -> void {
        disc[x] = low[x] = timp++;
        st.push_back(x);
        in[x] = true;

        for (int32_t y : g[x]) {
            if (disc[y] == -1) {
                self(self, y);
                low[x] = std::min(low[x], low[y]);
            } else if (in[y]) {
                low[x] = std::min(low[x], disc[y]);
            }
        }

        if (disc[x] == low[x]) {
            while (true) {
                in[st.back()] = false;
                scc_id[st.back()] = scc_counter;
                
                if (st.back() == x) {
                    st.pop_back();
                    break;
                }

                st.pop_back();
            }

            scc_counter++;
        }
    };

    for (int32_t i = 0; i < num_nodes; ++i) {
        if (disc[i] == -1) {
            tarjan_dfs(tarjan_dfs, i);
        }
    }

    bool ok = true;
    for (int32_t i = 0; i < num_var; ++i) {
        int32_t x = i << 1, y = x + 1;

        if (scc_id[x] == scc_id[y]) {
            ok = false;
            break;
        }
    }

    if (ok) {
    } else {
    }
}

void tarjan_bridge_and_articulation_points(std::vector<std::vector<int32_t>>& g, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(g.size());
    std::vector<int32_t> disc(n, -1), low(n, -1), bridges, art_points;
    int32_t timp = 0;

    auto dfs = [&](auto&& dfs, int32_t x, int32_t y) -> void {
        disc[x] = low[x] = timp++;
        int32_t nrc = 0;

        for (int32_t y : g[x]) {
            if (y == p) {
                continue;
            }

            if (disc[y] != -1) {
                low[x] = std::min(low[x], disc[y]);
            } else {
                dfs(dfs, y, x);
                low[x] = std::min(low[x], low[y]);

                if (low[y] >= disc[x] && p != -1) {
                    art_points.push_back(x);
                }
            }

            nrc++;
        }
    };
}