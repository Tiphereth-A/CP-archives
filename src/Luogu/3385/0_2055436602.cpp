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
const int N = 2e3 + OFFSET, M = 2e5 + OFFSET, K = 21;
const int MOD = 1e9 + 7;
const db EPS = 1e-6;
const int INF = 0x3f3f3f3f;
const i64 INFLL = 0x3f3f3f3f3f3f3f3f;
const db PI = acos(-1.0);
struct Edge {
    i64 w;
    int to, next;
    Edge(i64 _w = 0, int _to = 0, int _next = 0):
        w(_w), to(_to), next(_next) {}
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y, i64 w = 1) {
    e[++cnt_edge] = Edge(w, y, head[x]);
    head[x] = cnt_edge;
}
i64 d[N], cnt[N];
bool vis[N];
bool spfa(int n, int start = 1) {
    _set_inf_n(d, n + 1);
    _set_nul_n(cnt, n + 1);
    _set_nul_n(vis, n + 1);
    queue<int> q;
    q.push(start);
    vis[start] = 1;
    d[start] = 0;
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = 0;
        for (int i = head[now], to; i; i = e[i].next) {
            to = e[i].to;
            if (e[i].w + d[now] < d[to]) {
                d[to] = e[i].w + d[now];
                if (!vis[to]) {
                    if (++cnt[to] >= n) return 0;
                    q.push(to);
                    vis[to] = 1;
                }
            }
        }
    }
    return 1;
}
int main() {
#ifdef _LOCAL_
    clock_t _CLOCK_ST = clock();
#endif
    int kase;
    scanf("%d", &kase);
    while (kase--) {
        int n, m;
        scanf("%d%d", &n, &m);
        int x, y;
        i64 w;
        _for(i, 1, m) {
            scanf("%d%d%lld", &x, &y, &w);
            addEdge(x, y, w);
            if (w >= 0) addEdge(y, x, w);
        }
        puts(spfa(n, 1) ? "NO" : "YES");
    __end_kase:;
        cnt_edge = 0;
        _set_nul_n(head, n + 1);
    }
FINISHED:
#ifdef _LOCAL_
    std::cerr << "\n---\n"
              << "Time used: " << clock() - _CLOCK_ST << std::endl;
#endif
    return 0;
}