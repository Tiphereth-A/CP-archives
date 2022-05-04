#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using pii = pair<int, int>;
#define _for(i, l, r, vals...) for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
template <class T>
bool chkmin(T &a, T b) { return b < a ? a = b, true : false; }
template <class T>
bool chkmax(T &a, T b) { return a < b ? a = b, true : false; }
const uint32_t OFFSET = 5;
const uint32_t N = 1e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
const uint32_t MOD = 1e9 + 7;
const double EPS = 1e-6;
const int INF = 0x3f3f3f3f;
const i64 INFLL = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1.0);
const pii DIR4[4] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
const pii DIR8[8] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
const int EXP10[10] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
namespace SAT_2 {
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
int n;
bool init(int _n, int m, const pair<int, int> *restricts) {
    n = _n;
    for (int i = 1; i <= m; ++i) {
        auto &[x, y] = restricts[i];
        addEdge(x, y + (y % 2 ? 1 : -1));
        addEdge(y, x + (x % 2 ? 1 : -1));
    }
    for (int i = 1; i <= n * 2; ++i)
        if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= n * 2; ++i)
        if (i % 2 && scc_id[i] == scc_id[i + 1]) return false;
    return true;
}
bool possible_value(int x) { return scc_id[x] < scc_id[x + (x % 2 ? 1 : -1)]; }
}  // namespace SAT_2
constexpr auto __STATIC__ = []() { return 0.0; }();
pair<int, int> a[M];
inline auto solve() -> void {
    int n, m;
    cin >> n >> m;
    _for(i, 1, m) cin >> a[i].first >> a[i].second;
    if (!SAT_2::init(n, m, a)) {
        cout << "NIE";
        return;
    }
    _for(i, 1, n * 2)
        if (SAT_2::possible_value(i)) cout << i << '\n';
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