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
const int N = 100 + OFFSET, M = 2e5 + OFFSET, K = 21;
const int MOD = 1e9 + 7;
const db EPS = 1e-6;
const int INF = 0x3f3f3f3f;
const i64 INFLL = 0x3f3f3f3f3f3f3f3f;
const db PI = acos(-1.0);
struct Edge {
    int w, to, next;
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y, int w = 1) {
    e[++cnt_edge] = {w, y, head[x]};
    head[x] = cnt_edge;
}
int in[N], out[N];
i64 neu[N];
int main() {
#ifndef ONLINE_JUDGE
    clock_t _CLOCK_ST = clock();
#endif
    int n, p;
    scanf("%d%d", &n, &p);
    queue<int> q;
    i64 c, u;
    _for(i, 1, n) {
        scanf("%lld%lld", &c, &u);
        if (c) {
            q.push(i);
            neu[i] = c;
        } else
            neu[i] = c - u;
    }
    int x, y;
    i64 w;
    _for(i, 1, p) {
        scanf("%d%d%lld", &x, &y, &w);
        addEdge(x, y, w);
        ++in[y];
        ++out[x];
    }
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        if (neu[now] <= 0) continue;
        for (int i = head[now], to; i; i = e[i].next) {
            neu[to = e[i].to] += e[i].w * neu[now];
            if (!(--in[to])) q.push(to);
        }
    }
    bool f = 1;
    _for(i, 1, n)
        if (!out[i] && (neu[i] > 0)) {
            f = 0;
            printf("%d %lld\n", i, neu[i]);
        }
    if (f) puts("NULL");
FINISHED:
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time used: " << clock() - _CLOCK_ST << std::endl;
#endif
    return 0;
}