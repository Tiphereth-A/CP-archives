#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _rfor(i, r, l, vals...) for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vals; i >= i##end; --i)
#define _foreach_val(i, container) for (auto i : container)
#define _foreach_ref(i, container) for (auto &i : container)
#define _foreach_cref(i, container) for (const auto &i : container)
#define _foreach_rref(i, container) for (auto &&i : container)
#define _foreach_iter(it, container) for (auto it = (container).begin(); it != (container).end(); ++it)
#define _foreach_iter_range(it, container, l, r) for (auto it = (container).begin() + l; it != (container).begin() + r; ++it)
#define _set_nul_n(a, n) memset(a, 0, sizeof(*(a)) * (n))
template <class T>
bool chkmin(T &a, T b) { return b < a ? a = b, true : false; }
template <class T>
bool chkmax(T &a, T b) { return a < b ? a = b, true : false; }
const uint32_t OFFSET = 5;
const uint32_t N = 2e6 + OFFSET, M = 2e6 + OFFSET;
struct Edge {
    int to, next;
    Edge(int _to = 0, int _next = 0):
        to(_to), next(_next) {}
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y) {
    e[++cnt_edge] = Edge(y, head[x]);
    head[x] = cnt_edge;
}
#define _for_graph(head, e, i, now) for (int i = head[now], to = e[i].to; i; to = e[i = e[i].next].to)
int dfn[N], low[N], cnt_dfn;
stack<int> stk;
bool in_stk[N];
int scc_id[N], cnt_scc;
void tarjan(int now) {
    dfn[now] = low[now] = ++cnt_dfn;
    stk.push(now);
    in_stk[now] = 1;
    _for_graph(head, e, i, now)
        if (!dfn[to]) {
            tarjan(to);
            chkmin(low[now], low[to]);
        } else if (in_stk[to])
            chkmin(low[now], dfn[to]);
    if (dfn[now] == low[now]) {
        ++cnt_scc;
        while (stk.top() != now) {
            scc_id[stk.top()] = cnt_scc;
            in_stk[stk.top()] = 0;
            stk.pop();
        }
        scc_id[stk.top()] = cnt_scc;
        in_stk[stk.top()] = 0;
        stk.pop();
    }
}
#define MULTI_CASES
inline auto solve() -> void {
    int n, m;
    cin >> n >> m;
    _set_nul_n(dfn, n * 2 + 1);
    _set_nul_n(low, n * 2 + 1);
    _set_nul_n(scc_id, n * 2 + 1);
    _set_nul_n(in_stk, n * 2 + 1);
    _set_nul_n(head, n * 2 + 1);
    cnt_dfn = cnt_scc = cnt_edge = 0;
    char c1, c2;
    _for(i, 1, m, x, y) {
        cin >> c1 >> x >> c2 >> y;
        addEdge(x + (c1 == 'm') * n, y + (c2 == 'h') * n);
        addEdge(y + (c2 == 'm') * n, x + (c1 == 'h') * n);
    }
    _for(i, 1, n * 2)
        if (!dfn[i]) tarjan(i);
    _for(i, 1, n)
        if (scc_id[i] == scc_id[i + n]) {
            cout << "BAD\n";
            return;
        }
    cout << "GOOD\n";
}
int main() {
#ifdef _LOCAL_
    auto _CLOCK_ST = std::chrono::steady_clock::now();
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifdef MULTI_CASES
    int _t;
    cin >> _t;
    while (_t--)
#endif
        solve();
#ifdef _LOCAL_
    std::clog << "\n---\n"
              << "Time used: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _CLOCK_ST).count() << " ms" << std::endl;
#endif
    return 0;
}