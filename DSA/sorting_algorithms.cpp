#include <cstdint>
#include <vector>
#include <random>
#include <chrono>

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

void swap(int32_t& a, int32_t& b) {
    a ^= b;
    b ^= a;
    a ^= b;
}

struct State {
    ///cod
};

void bubble_sort(std::vector<int32_t>& a, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = i + 1; j < n; ++j) {
            if (a[i] > a[j]) {
                swap(a[i], a[j]);
            }
        }
    }
}

void select_sort(std::vector<int32_t>& a, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    for (int32_t i = 0; i < n; ++i) {
        int32_t pm = i;
        for (int32_t j = i + 1; j < n; ++j) {
            if (a[j] < a[pm]) {
                pm = j;
            }
        }

        if (pm != i) {
            swap(a[i], a[pm]);
        }
    }
}

void insertion_sort(std::vector<int32_t>& a, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    for (int32_t i = 1; i < n; ++i) {
        int32_t k = a[i];
        int32_t j = i - 1;

        while (j >= 0 && a[j] > k) {
            a[j + 1] = a[j];
            --j;
        }

        a[j + 1] = k;
    }
}

void gnome_sort(std::vector<int32_t>& a, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    int32_t poz = 1;

    while (poz < n) {
        if (!poz || a[poz] >= a[poz - 1]) {
            poz++;
        } else {
            swap(a[poz], a[poz - 1]);
            poz--;
        }
    }
}

void quicksort(std::vector<int32_t>& a, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    
    auto f = [&](auto&& f, int32_t st, int32_t dr, std::vector<int32_t>& a) {
        if (st == dr) {
            return;
        }
        
        int32_t p = rng() % (dr - st + 1) + st;
        std::vector<int32_t> l, r;

        for (int32_t i = st; i <= dr; ++i) {
            if (i == p) {
                continue;
            }

            if (a[i] < a[p]) {
                l.push_back(a[i]);
            } else if (a[i] > a[p]) {
                r.push_back(a[i]);
            } else { ///for equal distribution
                if (l.size() <= r.size()) {
                    l.push_back(a[i]);
                } else {
                    r.push_back(a[i]);
                }
            }
        }

        f(f, st, p - 1, l);
        f(f, p + 1, dr, r);
    };

    f(f, 0, n - 1, a);
}

void mergesort(std::vector<int32_t>& a, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    
    auto f = [&](auto&& f, int32_t st, int32_t dr, std::vector<int32_t>& a) {
        if (dr - st <= 1) {
            if (a[st - st] > a[dr - st]) {
                swap(a[st - st], a[dr - st]);
            }

            return;
        }

        int32_t n = static_cast<int32_t>(a.size());
        int32_t mij = st + ((dr - st) >> 1);
        std::vector<int32_t> l(a.begin(), a.begin() + mij), r(a.begin() + mij, a.end());
        f(f, st, mij, l);
        f(f, mij + 1, dr, r);
        std::vector<int32_t> v;
        int32_t i = 0, j = 0;

        while (i < mij && j < dr - st + 1 - mij) {
            if (l[i] <= r[j]) {
                v.push_back(l[i]);
                i++;
            } else {
                v.push_back(r[j]);
                j++;
            }
        }

        while (i < mij) {
            v.push_back(l[i]);
            i++;
        }

        std::vector<int32_t>().swap(l);

        while (j < dr - st + 1 - mij) {
            v.push_back(r[j]);
            j++;
        }

        std::vector<int32_t>().swap(r);
        a = v;
        std::vector<int32_t>().swap(v);
    };

    f(f, 0, n - 1, a);
}

void heapsort(std::vector<int32_t>& a, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    int32_t start = n >> 1, end = n;

    while (end > 1) {
        if (start) {
            start--;
        } else {
            end--;
            swap(a[0], a[end]);
        }

        int32_t rad = start;

        while ((rad << 1) < end) {
            int32_t ch = rad << 1;

            if (ch + 1 < end && a[ch] < a[ch + 1]) {
                ch++;
            }

            if (a[rad] < a[ch]) {
                swap(a[rad], a[ch]);
                rad = ch;
            } else {
                break;
            }
        }
    }
}

void radix_sort_base_65536(std::vector<int32_t>& a, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(a.size());
    std::vector<int32_t> fr(65536, 0), v(n);

    for (int32_t pas = 0; pas < 2; ++pas) {
        fill(fr.begin(), fr.end(), 0);
        for (int32_t i = 0; i < n; ++i) {
            fr[a[i] >> (pas << 4) & 0xffff]++;
        }

        for (int32_t i = 1; i < n; ++i) {
            fr[i] += fr[i - 1];
        }

        for (int32_t i = n - 1; i >= 0; --i) {
            v[--fr[a[i] >> (pas << 4) & 0xffff]] = a[i];
        }

        a = v;
    }

    std::vector<int32_t>().swap(v);
}