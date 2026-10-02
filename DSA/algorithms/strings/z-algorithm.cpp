#include "../../core/states.hpp"

void z_algorithm(std::string& s, std::string& t, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(s.size()), m = static_cast<int32_t>(t.size());
    std::vector<int32_t> z(n + m + 1, 0), v;
    std::string u = t + '$' + s;

    for (int32_t i = 1, l = 0, r = 0; i < static_cast<int32_t>(u.size()); ++i) {
        if (i <= r) {
            z[i] = std::min(r - i + 1, z[i - l]);
        }

        while (i + z[i] < static_cast<int32_t>(u.size()) && u[z[i]] == u[i + z[i]]) {
            z[i]++;
        }

        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (z[i + m + 1] == m) {
            v.push_back(i);
        }
    }
}