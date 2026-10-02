#include "../../core/states.hpp"

void extended_euclid(int32_t a, int32_t b, std::vector<State>& states) {
    auto gcde = [](auto&& gcde, int32_t a, int32_t b, int32_t& x, int32_t& y) -> int32_t {
        if (!b) {
            x = 1;
            y = 0;
            return a;
        }

        int32_t x1, y1;
        int32_t g = gcde(gcde, b, a % b, x1, y1);
        x = y1;
        y = x1 - (a / b) * y1;
        return g;
    };

    int32_t x, y;
    gcde(gcde, a, b, x, y);
    ///x is the modular inverse of a mod b
}