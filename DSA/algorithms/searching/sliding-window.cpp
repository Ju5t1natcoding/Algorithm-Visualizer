#include "../../core/states.hpp"
#include <unordered_map>
#include <array>

void sliding_window_longest_increaseing_sequence_vector(std::vector<int32_t>& a, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    int32_t l = 0, ans = 1;

    for (int32_t r = 1; r < n; ++r) {
        while (l < r && a[l] >= a[r]) {
            l++;
        }

        ans = std::max(ans, r - l + 1);
    }
}

void sliding_window_longest_equal_sequence_vector(std::vector<int32_t>& a, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    int32_t l = 0, ans = 1;

    for (int32_t r = 1; r < n; ++r) {
        while (l < r && a[l] != a[r]) {
            l++;
        }

        ans = std::max(ans, r - l + 1);
    }
}

void sliding_window_longest_sequence_with_distinct_elements_vector(std::vector<int32_t>& a, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    std::unordered_map<int32_t, int32_t> mp;
    int32_t l = 0, ans = 1;
    mp[a[0]] = 1;

    for (int32_t r = 1; r < n; ++r) {
        mp[a[r]]++;

        if (mp[a[r]] > 1) {
            while(l < r && mp[a[r]] > 1) {
                mp[a[l]]--;

                if (!mp[a[l]]) {
                    mp.erase(a[l]);
                }

                l++;
            }
        }

        ans = std::max(ans, r - l + 1);
    }
}

void sliding_window_longest_increaseing_sequence_string(std::string& s, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(s.size());
    int32_t l = 0, ans = 1;

    for (int32_t r = 1; r < n; ++r) {
        while (l < r && s[l] >= s[r]) {
            l++;
        }

        ans = std::max(ans, r - l + 1);
    }
}

void sliding_window_longest_equal_sequence_string(std::string& s, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(s.size());
    int32_t l = 0, ans = 1;

    for (int32_t r = 1; r < n; ++r) {
        while (l < r && s[l] != s[r]) {
            l++;
        }

        ans = std::max(ans, r - l + 1);
    }
}

void sliding_window_longest_sequence_with_distinct_elements_string(std::string& s, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(s.size());
    std::array<int32_t, 256> mp;
    int32_t l = 0, ans = 1;
    mp[s[0]] = 1;

    for (int32_t r = 1; r < n; ++r) {
        mp[s[r]]++;

        if (mp[s[r]] > 1) {
            while(l < r && mp[s[r]] > 1) {
                mp[s[l]]--;
                l++;
            }
        }

        ans = std::max(ans, r - l + 1);
    }
}