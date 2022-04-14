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
const int N = 1e4 + OFFSET, M = 2e5 + OFFSET, K = 21;
const int MOD = 1e9 + 7;
const db EPS = 1e-6;
const int INF = 0x3f3f3f3f;
const i64 INFLL = 0x3f3f3f3f3f3f3f3f;
const db PI = acos(-1.0);
bool g[N][N];
bool vis[N], valid[N];
int d[N];
int main() {
#ifndef ONLINE_JUDGE
    clock_t _CLOCK_ST = clock();
#endif
    int n, m;
    scanf("%d%d", &n, &m);
    int x, y;
    _for(i, 1, m) {
        scanf("%d%d", &x, &y);
        if (x != y) g[x][y] = 1;
    }
    scanf("%d%d", &x, &y);
    queue<int> q;
    q.push(y);
    vis[y] = 1;
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        _for(i, 1, n)
            if (!vis[i] && g[i][now]) {
                q.push(i);
                vis[i] = 1;
            }
    }
    if (!vis[x]) _run_exit(puts("-1"));
    _for(i, 1, n)
        if (vis[i]) {
            valid[i] = 1;
            _for(j, 1, n)
                if (g[i][j] && !vis[j]) _run_break(valid[i] = 0);
        }
    if (!valid[x]) _run_exit(puts("-1"));
    queue<pii> q2;
    q2.emplace(x, 0);
    while (!q2.empty()) {
        pii now = q2.front();
        q2.pop();
        if (now.first == y) _run_exit(printf("%d", now.second));
        _for(i, 1, n)
            if (g[now.first][i] && valid[i] && !d[i]) q2.emplace(i, d[i] = now.second + 1);
    }
    puts("-1");
FINISHED:
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time used: " << clock() - _CLOCK_ST << std::endl;
#endif
    return 0;
}