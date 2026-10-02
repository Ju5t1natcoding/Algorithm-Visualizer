#include "../../core/states.hpp"

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