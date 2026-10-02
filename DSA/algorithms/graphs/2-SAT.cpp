#include "../../core/states.hpp"
#include <unordered_map>
#include <algorithm>
#include <sstream>

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
        ///cod
    } else {
        ///cod
    }
}