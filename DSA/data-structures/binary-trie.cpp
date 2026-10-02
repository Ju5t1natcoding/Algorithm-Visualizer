#include "binary-trie.hpp"

BinaryTrie::BinaryTrie() {
    tr.assign(1, TrieNode());
}

void BinaryTrie::insert(int32_t x) {
    int32_t nod = 0;
    for (int32_t b = 31; b >= 0; --b) {
        int32_t bit = x >> b & 1;
        
        if (tr[nod].nxt[bit] == -1) {
            int32_t nw = static_cast<int32_t>(tr.size());
            tr.emplace_back(nod, bit);
            tr[nod].nxt[bit] = nw;
        }

        nod = tr[nod].nxt[bit];
        tr[nod].pass++;
    }

    tr[nod].end++;
}

int32_t BinaryTrie::walk(int32_t x) {
    int32_t nod = 0;
    for (int32_t b = 31; b >= 0; --b) {
        int32_t nxt = tr[nod].nxt[x >> b & 1];

        if (nxt == -1) {
            return -1;
        }

        nod = nxt;
    }

    return nod;
}

bool BinaryTrie::erase(int32_t x) {
    int32_t nod = walk(x);

    if (nod == -1 || !tr[nod].end) {
        return false;
    }

    tr[nod].end--;

    while (nod) {
        int32_t p = tr[nod].parent;

        if (--tr[nod].pass == 0) {
            tr[p].nxt[tr[nod].p_val] = -1;
        }

        nod = p;
    }

    return true;
}

bool BinaryTrie::search(int32_t x) {
    int32_t nod = walk(x);

    if (nod == -1) {
        return false;
    }

    bool ok = tr[nod].end > 0;
    return ok;
}

int32_t BinaryTrie::max_xor(int32_t x) {
    int32_t nod = 0;
    uint32_t ans = 0;

    for (int32_t b = 31; b >= 0; --b) {
        int32_t bit = x >> b & 1;

        if (tr[nod].nxt[bit ^ 1] != -1) {
            ans |= 1u << b;
            nod = tr[nod].nxt[bit ^ 1];
        } else if (tr[nod].nxt[bit] != -1) {
            nod = tr[nod].nxt[bit];
        } else {
            return -1;
        }
    }

    return static_cast<int32_t>(ans);
}

int32_t BinaryTrie::min_xor(int32_t x) {
    int32_t nod = 0;
    uint32_t ans = 0;

    for (int32_t b = 31; b >= 0; --b) {
        int32_t bit = x >> b & 1;

        if (tr[nod].nxt[bit] != -1) {
            nod = tr[nod].nxt[bit];
        } else if (tr[nod].nxt[bit ^ 1] != -1) {
            ans |= 1u << b;
            nod = tr[nod].nxt[bit ^ 1];
        } else {
            return -1;
        }
    }

    return static_cast<int32_t>(ans);
}

int32_t BinaryTrie::countLess(int32_t x) {
    int32_t nod = 0, ans = 0;
    for (int32_t b = 31; b >= 0 && nod != -1; --b) {
        int32_t bit = x >> b & 1;

        if (bit && tr[nod].nxt[0] != -1) {
            ans += tr[tr[nod].nxt[0]].pass;
        }

        nod = tr[nod].nxt[bit];
    }

    return ans;
}

int32_t BinaryTrie::kth(int32_t k) {
    int32_t total = 0;
    for (int32_t c = 0; c < 2; ++c) {
        if (tr[0].nxt[c] != -1) {
            total += tr[tr[0].nxt[c]].pass;
        }
    }

    if (k < 1 || k > total) {
        return -1;
    }

    int32_t nod = 0;
    uint32_t ans = 0;

    for (int32_t b = 31; b >= 0; --b) {
        int32_t cnt = (tr[nod].nxt[0] == -1) ? 0 : tr[tr[nod].nxt[0]].pass;

        if (k <= cnt) {
            nod = tr[nod].nxt[0];
        } else {
            k -= cnt;
            nod = tr[nod].nxt[1];
            ans |= 1u << b;
        }
    }

    return static_cast<int32_t>(ans);
}

int32_t BinaryTrie::countXorLess(int32_t x, int32_t k) {
    int32_t nod = 0, ans = 0;
    for (int32_t b = 31; b >= 0 && nod != -1; --b) {
        int32_t xb = x >> b & 1;
        int32_t kb = k >> b & 1;

        if (kb) {
            int32_t same = tr[nod].nxt[xb];

            if (same != -1) {
                ans += tr[same].pass;
            }

            nod = tr[nod].nxt[xb ^ 1];
        } else {
            nod = tr[nod].nxt[xb];
        }
    }

    return ans;
}