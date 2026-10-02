#include "../../core/states.hpp"

void two_pointers_2sum_on_sorted_array(std::vector<int32_t>& a, int64_t target, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    int32_t l = 0, r = n - 1;
    int64_t sum = 0;
    std::pair<int32_t, int32_t> ans;

    while (l < r) {
        if (a[l] + a[r] == target) {
            ans = {l, r};
            break;
        } else if (a[l] + a[r] > target) {
            r--;
        } else {
            l++;
        }
    }
}

void two_pointers_palindrome_check_vector(std::vector<int32_t>& a, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    int32_t l = 0, r = n - 1;
    bool ok = true;

    while (l < r) {
        if (a[l] != a[r]) {
            ok = false;
            break;
        }

        l++;
        r--;
    }
}

void two_pointers_palindrome_check_string(std::string& s, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(s.size());
    int32_t l = 0, r = n - 1;
    bool ok = true;

    while (l < r) {
        if (s[l] != s[r]) {
            ok = false;
            break;
        }

        l++;
        r--;
    }
}