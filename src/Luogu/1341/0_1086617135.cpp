#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128_t;
using u128 = __uint128_t;
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
const int N = 1 << 8, M = N * N + OFFSET, K = 21;
const int MOD = 1e9 + 7;
const db EPS = 1e-6;
const int INF = 0x3f3f3f3f;
const i64 INFLL = 0x3f3f3f3f3f3f3f3f;
const db PI = acos(-1.0);
bool g[N][N];
char ans[M];
int n;
void dfs(int now) {
    _for(i, 0, N - 1) if (g[now][i]) {
        g[now][i] = g[i][now] = 0;
        dfs(i);
    }
    ans[n--] = now;
}
int d[N];
int main() {
#ifndef ONLINE_JUDGE
    clock_t _CLOCK_ST = clock();
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    char x, y;
    _for(i, 1, n) {
        cin >> x >> y;
        g[x][y] = g[y][x] = 1;
        ++d[x];
        ++d[y];
    }
    int cnt = 0, start = 0;
    _for(i, 0, N - 1) if (d[i] & 1) {
        ++cnt;
        if (!start) start = i;
    }
    if (cnt && cnt != 2) _run_exit(cout << "No Solution\n");
    if (!start) _for(i, 0, N - 1) if (d[i]) _run_break(start = i);
    dfs(start);
    cout << ans << '\n';
FINISHED:
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time used: " << clock() - _CLOCK_ST << std::endl;
#endif
    return 0;
}
