#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using db = double;
using ldb = long double;
using pii = pair<int, int>;
using vi = vector<int>;
using qi = queue<int>;
using dqi = deque<int>;
using pqi = priority_queue<int>;
using si = set<int>;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
#define _rfor(i, r, l) for (decltype(l + r) i = (r); i >= (l); --i)
#define _ins(a) std::inserter((a), (a).begin())
#define _all(a) (a).begin(), (a).end()
#define _set_nul(a) memset(a, 0, sizeof(a))
#define _set_inf(a) memset(a, 0x3f, sizeof(a))
#define _set_nul_n(a, n) memset(a, 0, sizeof(a[0]) * (n))
#define _set_inf_n(a, n) memset(a, 0x3f, sizeof(a[0]) * (n))
#define _fin goto FINISHED
#define _divb(l, r, n, expressions)                   \
    for (decltype(n) l = 2, r; l <= (n); l = r + 1) { \
        r = (n) / ((n) / l);                          \
        expressions;                                  \
    }
#define _run_exit(expressions) _run_return(expressions, 0)
#define _run_return(expressions, val) return (expressions), val
#define _run_fin(expressions) \
    {                         \
        expressions;          \
        _fin;                 \
    }
#define _run_break(expressions) \
    {                           \
        expressions;            \
        break;                  \
    }
#define _run_continue(expressions) \
    {                              \
        expressions;               \
        continue;                  \
    }
#define _mid(l, r) ((l) + (((r) - (l)) >> 1))
#define _len(l, r) ((r) - (l) + 1)
#define _lowbit(x) (1 << __builtin_ctz(x))
#define _lowbit_64(x) (1 << __builtin_ctzll(x))
#define _debug                                              \
    {                                                       \
        fprintf(stderr, "%d %s\n", __LINE__, __FUNCTION__); \
        fflush(stderr);                                     \
    }
template <class T>
bool chkmin(T &a, T b) { return b < a ? a = b, true : false; }
template <class T>
bool chkmax(T &a, T b) { return a < b ? a = b, true : false; }
const int OFFSET = 5;
const int N = 4e5 + OFFSET, M = 2e5 + OFFSET, K = 10;
const int MOD = 1e9 + 7;
const db EPS = 1e-6;
const int INF = 0x3f3f3f3f;
const i64 INFLL = 0x3f3f3f3f3f3f3f3f;
const db PI = acos(-1.0);
template <class _T = std::size_t, const std::size_t _CHILD = K, const std::size_t _N = N, const bool _clear = false>
class Huffman_tree {
  protected:
    struct Node {
        _T w;
        std::size_t child[_CHILD];
        std::size_t cnt_child;
    } nodes[_N];
    bool _build;
    std::size_t cnt_nodes, max_child_size, leaves;

  public:
    Huffman_tree(std::size_t max_child = 2):
        max_child_size(max_child) {
        if (_clear) memset(nodes, cnt_nodes = leaves = _build = 0, sizeof(nodes));
    }
    void clear() { memset(nodes, cnt_nodes = leaves = max_child_size = _build = 0, sizeof(nodes)); }
    void build(const std::vector<_T> &frenqucy, std::size_t max_child) {
        if (_build) return;
        max_child_size = max_child;
        cnt_nodes = frenqucy.size();
        for (std::size_t i = 1; i <= cnt_nodes; ++i) {
            nodes[i].w = frenqucy[i - 1];
            nodes[i].cnt_child = 0;
        }
        cnt_nodes += ((max_child - 1) - ((cnt_nodes - 1) % (max_child - 1))) % (max_child - 1);
        std::priority_queue<std::pair<_T, int>, std::vector<std::pair<_T, int>>, std::greater<std::pair<_T, int>>> q;
        for (std::size_t i = 1; i <= cnt_nodes; ++i) q.emplace(nodes[i].w, i);
        while (q.size() > 1) {
            ++cnt_nodes;
            for (std::size_t i = 1; i <= max_child_size; ++i) {
                if (q.empty()) break;
                nodes[cnt_nodes].w += q.top().first;
                nodes[cnt_nodes].child[++nodes[cnt_nodes].cnt_child] = q.top().second;
                q.pop();
            }
            q.emplace(nodes[cnt_nodes].w, cnt_nodes);
        }
        _build = 1;
    }
    std::vector<std::string> encode(const std::vector<_T> &frenqucy, const std::string &char_set = "01") {
        if (!_build) build(frenqucy, char_set.length());
        std::vector<std::string> ret;
        ret.resize(frenqucy.size());
        std::queue<std::pair<std::size_t, std::string>> q;
        q.emplace(cnt_nodes, "");
        while (!q.empty()) {
            std::pair<std::size_t, std::string> now = q.front();
            q.pop();
            const Node &now_node = nodes[now.first];
            for (std::size_t i = 1; i <= now_node.cnt_child; ++i) {
                const Node &next_node = nodes[now_node.child[i]];
                if (next_node.cnt_child == 0) {
                    if (now_node.child[i] <= ret.size()) ret[now_node.child[i] - 1] = now.second + char_set[i - 1];
                    continue;
                } else
                    q.emplace(now_node.child[i], now.second + char_set[i - 1]);
            }
        }
        return ret;
    }
    std::vector<std::size_t> get_depth(const std::vector<_T> &frenqucy, const std::size_t max_child = 2) {
        if (!_build) build(frenqucy, max_child);
        std::vector<std::size_t> ret;
        ret.resize(frenqucy.size());
        std::queue<std::pair<std::size_t, std::size_t>> q;
        q.emplace(cnt_nodes, 0);
        while (!q.empty()) {
            std::pair<std::size_t, std::size_t> now = q.front();
            q.pop();
            const Node &now_node = nodes[now.first];
            for (std::size_t i = 1; i <= now_node.cnt_child; ++i) {
                const Node &next_node = nodes[now_node.child[i]];
                if (next_node.cnt_child == 0) {
                    if (now_node.child[i] <= ret.size()) ret[now_node.child[i] - 1] = now.second + 1;
                    continue;
                } else
                    q.emplace(now_node.child[i], now.second + 1);
            }
        }
        return ret;
    }
};
Huffman_tree<i64> hf;
int main() {
#ifndef ONLINE_JUDGE
    clock_t _CLOCK_ST = clock();
#endif
    int n, k;
    scanf("%d%d", &n, &k);
    vector<i64> frq;
    i64 _;
    _for(i, 1, n) {
        scanf("%lld", &_);
        frq.push_back(_);
    }
    vector<size_t> dep = hf.get_depth(frq, k);
    size_t len = 0, maxd = 0;
    _for(i, 0, n - 1) {
        len += frq[i] * dep[i];
        chkmax(maxd, dep[i]);
    }
    printf("%lld\n%lld", len, maxd);
FINISHED:
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time used: " << clock() - _CLOCK_ST << std::endl;
#endif
    return 0;
}