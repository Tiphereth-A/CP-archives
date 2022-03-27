#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
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
#define _for_graph(head, e, i, now) for (int i = head[now], to = e[i].to; i; to = e[i = e[i].next].to)
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
bool chkmin(T& a, T b) { return b < a ? a = b, true : false; }
template <class T>
bool chkmax(T& a, T b) { return a < b ? a = b, true : false; }
const int OFFSET = 5;
const int N = 100 + OFFSET, M = 1e4 + OFFSET, K = 21;
const int MOD = 1e9 + 7;
const db EPS = 1e-6;
const int INF = 0x3f3f3f3f;
const i64 INFLL = 0x3f3f3f3f3f3f3f3f;
const db PI = acos(-1.0);
struct Edge {
    int to, next;
    Edge(int _to = 0, int _next = 0) : to(_to), next(_next) {}
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y) {
    e[++cnt_edge] = Edge(y, head[x]);
    head[x] = cnt_edge;
}
int dfn[N], low[N], cnt_dfn;
stack<int> stk;
bool in_stk[N];
int scc_id[N], scc_size[N], cnt_scc;
void tarjan(int now) {
    in_stk[now] = 1;
    dfn[now] = low[now] = ++cnt_dfn;
    stk.push(now);
    _for_graph(head, e, i, now) if (!dfn[to]) {
        tarjan(to);
        chkmin(low[now], low[to]);
    }
    else if (in_stk[to]) chkmin(low[now], dfn[to]);
    if (dfn[now] == low[now]) {
        ++cnt_scc;
        while (stk.top() != now) {
            ++scc_size[scc_id[stk.top()] = cnt_scc];
            in_stk[stk.top()] = 0;
            stk.pop();
        }
        ++scc_size[scc_id[stk.top()] = cnt_scc];
        in_stk[stk.top()] = 0;
        stk.pop();
    }
}
int in[N], out[N];
int main() {
#ifndef ONLINE_JUDGE
    clock_t _CLOCK_ST = clock();
#endif
    int n;
    scanf("%d", &n);
    int x;
    _for(i, 1, n) while (scanf("%d", &x), x) addEdge(i, x);
    _for(i, 1, n) if (!dfn[i]) tarjan(i);
    _for(i, 1, n) _for_graph(head, e, j, i) {
        if (scc_id[to] == scc_id[i]) continue;
        ++in[scc_id[to]];
        ++out[scc_id[i]];
    }
    int cnt_in = 0, cnt_out = 0;
    _for(i, 1, cnt_scc) {
        cnt_in += !in[i];
        cnt_out += !out[i];
    }
    printf("%d\n%d", cnt_in, cnt_scc == 1 ? 0 : max(cnt_in, cnt_out));
FINISHED:
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time used: " << clock() - _CLOCK_ST << std::endl;
#endif
    return 0;
}