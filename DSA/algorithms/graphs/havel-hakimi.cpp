#include "../../core/states.hpp"
#include <algorithm>

///test if a graph is valid based on the degrees of the nodes
void havel_hakimi(std::vector<int32_t>& deg, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(deg.size());
    std::sort(deg.begin(), deg.end(), std::greater<int32_t>());
    bool ok = true;

    while (deg[0] > 0) {
        if (deg[0] >= n) {
            ///cod
            ok = false;
            break;
        }

        for (int i = 1; i <= deg[0]; ++i) {
            deg[i]--;

            if (deg[i] < 0) {
                ok = false;
                break;
            }
        }

        if (!ok) {
            ///cod
            break;
        }

        std::sort(deg.begin(), deg.end(), std::greater<int32_t>());
    }
}