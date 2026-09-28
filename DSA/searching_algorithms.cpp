#include <cstdint>
#include <vector>
#include <string>

struct State {
    ///cod
};

void linear_search(std::vector<int32_t>& a, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    ///cod - nuj de exemplu pe cautare liniara ce sa fac
}

void binary_search(std::vector<int32_t>& a, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    ///cod - trb sa vad din nou de exemplu ca la ala liniar
}

void ternary_search(std::vector<int32_t>& a, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    ///cod - din nou acelasi exemplu
}

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
    }
}

void sliding_window(std::vector<int32_t>& a, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    ///cod - si aici trb sa vad un exemplu
}