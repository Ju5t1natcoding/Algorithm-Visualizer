#include "trie.hpp"

Trie::Trie() {
    tr.assign(1, TrieNode());
}

void Trie::insert(const std::string& s) {
    int32_t nod = 0;
    for (char c : s) {
        if (!tr[nod].nxt.count(c)) {
            int32_t nw = static_cast<int32_t>(tr.size());
            tr.emplace_back(nod, c);
            tr[nod].nxt[c] = nw;
        }

        nod = tr[nod].nxt[c];
        tr[nod].pass++;
    }

    tr[nod].end++;
}

int32_t Trie::walk(const std::string& s) {
    int32_t nod = 0;
    for (char c : s) {
        if (!tr[nod].nxt.count(c)) {
            return -1;
        }

        nod = tr[nod].nxt[c];
    }

    return nod;
}

bool Trie::search(const std::string& s) {
    int32_t nod = walk(s);

    if (nod == -1) {
        return false;
    }

    bool ok = tr[nod].end > 0;
    return ok;
}

bool Trie::startsWith(const std::string& p) {
    int32_t nod = walk(p);
    return nod != -1;
}

int32_t Trie::countPrefix(const std::string& p) {
    int32_t nod = walk(p);
    return nod == -1 ? 0 : tr[nod].pass;
}

bool Trie::erase(const std::string& s) {
    int32_t nod = walk(s);

    if (nod == -1 || !tr[nod].end) {
        return false;
    }

    tr[nod].end--;

    while (nod) {
        int32_t p = tr[nod].parent;

        if (--tr[nod].pass == 0) {
            tr[p].nxt.erase(tr[nod].pc);
        }

        nod = p;
    }

    return true;
}

void Trie::collect(int32_t nod, std::string& curr, std::vector<std::string>& out) {
    if (tr[nod].end) {
        out.push_back(curr);
    }

    for (int k = 0; k < 256; ++k) {
        if (!tr[nod].nxt.count(k)) {
            continue;
        }

        curr.push_back(k);
        collect(tr[nod].nxt[k], curr, out);
        curr.pop_back();
    }
}

std::vector<std::string> Trie::autocomplete(const std::string& p) {
    std::vector<std::string> out;
    int nod = walk(p);

    if (nod == -1) {
        return out;
    }

    std::string curr = p;
    collect(nod, curr, out);
    return out;
}