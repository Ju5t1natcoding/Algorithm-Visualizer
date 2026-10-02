#include "../../core/states.hpp"
#include "../../data-structures/trie.hpp"
#include <algorithm>
#include <queue>

namespace {
    class AhoTrie: public Trie {
    public:
        int32_t dim() const {
            return static_cast<int32_t>(tr.size());
        }

        int32_t go(int32_t nod, char c) const {
            auto it = tr[nod].nxt.find(c);
            return it == tr[nod].nxt.end() ? -1 : it->second;
        }

        int32_t end_count(int32_t nod) {
            return tr[nod].end;
        }

        std::vector<std::pair<unsigned char, int32_t>> children(int32_t nod) const {
            std::vector<std::pair<unsigned char, int32_t>> out(tr[nod].nxt.begin(), tr[nod].nxt.end());
            std::sort(out.begin(), out.end());
            return out;
        }
    };
}

void aho_corasick(std::string& s, std::vector<std::string>& v, std::vector<State>& states) {
    int32_t n = static_cast<int32_t>(s.size());
    AhoTrie trie;
    std::vector<std::vector<int32_t>> ids(1);
    std::vector<int32_t> fail(1, -1), dict(1, -1);
    std::vector<std::pair<int32_t, int32_t>> matches;

    auto emit = [&](int32_t curr, int32_t other, int32_t pos, const char* note) {
        TrieState st;
        int32_t m = trie.dim();
        st.edges.resize(m);
        st.end.resize(m);

        for (int32_t x = 0; x < m; ++x) {
            st.edges[x] = trie.children(x);
            st.end[x] = trie.end_count(x);
        }

        st.fail = fail;
        st.dict = dict;
        st.matches = matches;
        st.curr = curr;
        st.other = other;
        st.pos = pos;
        st.note = note;
        states.push_back(std::move(st));
    };

    emit(0, -1, -1, "root");
    for (int32_t i = 0; i < static_cast<int32_t>(v.size()); ++i) {
        if (v[i].empty()) {
            continue;
        }

        trie.insert(v[i]);
        int32_t nod = trie.walk(v[i]);
        ids.resize(trie.dim());
        fail.assign(trie.dim(), -1);
        dict.assign(trie.dim(), -1);
        ids[nod].push_back(i);
        emit(nod, -1, -1, "pattern inserted");
    }

    std::queue<int32_t> q;
    for (auto& e : trie.children(0)) {
        fail[e.second] = 0;
        q.push(e.second);
    }

    emit(0, -1, -1, "children of root: fail = root");

    while (!q.empty()) {
        int32_t x = q.front();
        q.pop();
        int32_t f = fail[x];
        dict[x] = !ids[f].empty() ? f : dict[f];
        emit(x, f, -1, "dictionary link");

        for (auto& [c, ch] : trie.children(x)) {
            int32_t v = fail[x];

            while (v && trie.go(v, c) == -1) {
                emit(ch, v, -1, "v does not have edges, going up trough fail");
                v = fail[v];
            }

            int32_t y = trie.go(v, c);
            fail[ch] = (y != -1) ? y : 0;
            emit(ch, fail[ch], -1, "fail link set");
            q.push(ch);
        }
    }

    int32_t x = 0;
    emit(0, -1, -1, "start search");

    for (int32_t i = 0; i < n; ++i) {
        unsigned char c = static_cast<unsigned char>(s[i]);
        emit(x, -1, i, "reading character");

        while (x && trie.go(x, c) == -1) {
            emit(x, fail[x], i, "no edge exists, falling on fail link");
            x = fail[x];
        }

        int32_t nx = trie.go(x, c);

        if (nx != -1) {
            x = nx;
        }

        emit (x, -1, i, "advance");
        for (int32_t w = !ids[x].empty() ? x : dict[x]; w != -1; w = dict[w]) {
            for (int32_t id : ids[w]) {
                matches.push_back(std::make_pair(i, id));
            }

            emit(w, -1, i, "match");
        }
    }

    emit(x, -1, -1, "finished");
}