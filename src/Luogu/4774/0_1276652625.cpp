#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
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
#define _run_return(expressions, val) \
    {                                 \
        expressions;                  \
        return val;                   \
    }
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
template <class _T>
bool chkmin(_T &a, _T b) { return b < a ? a = b, true : false; }
template <class _T>
bool chkmax(_T &a, _T b) { return a < b ? a = b, true : false; }
const int OFFSET = 5;
const int N = 1e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
const int MOD = 1e9 + 7;
const db EPS = 1e-6;
const int INF = 0x3f3f3f3f;
const i64 INFLL = 0x3f3f3f3f3f3f3f3f;
const db PI = acos(-1.0);
i128 exgcd(i128 a, i128 b, i128 &x, i128 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    i128 res = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return res;
}
i64 a[N], p[N], _b[N], b[N];
i64 mindmg = 0;
bool excrt(i64 n, i64 &res) {
    i128 A, B, M = 1, pre_M;
    i128 x = 0, R;
    i128 g, lambda, mu;
    for (i64 i = 1; i <= n; ++i) {
        A = b[i] * (pre_M = M) % (B = p[i]);
        R = (a[i] - b[i] * x % B + B) % B;
        g = exgcd(A, B, lambda, mu);
        ((lambda %= B) += B) %= B;
        if (R % g) return false;
        M *= B / g;
        (x += lambda * (R / g) % (B / g) * pre_M % M) %= M;
    }
    res = x + (x < mindmg ? ((mindmg - x - 1) / M + 1) * M : 0);
    return true;
}
multiset<i64> all_b;
int main() {
#ifndef ONLINE_JUDGE
    clock_t _CLOCK_ST = clock();
#endif
    int kase;
    scanf("%d", &kase);
    while (kase--) {
        i64 n, m;
        scanf("%lld%lld", &n, &m);
        _for(i, 1, n) scanf("%lld", a + i);
        _for(i, 1, n) scanf("%lld", p + i);
        _for(i, 1, n) scanf("%lld", _b + i);
        i64 _;
        _for(i, 1, m) {
            scanf("%lld", &_);
            all_b.insert(_);
        }
        _for(i, 1, n) {
            auto now = all_b.upper_bound(a[i]);
            if (now != all_b.begin()) --now;
            b[i] = *now;
            all_b.erase(now);
            all_b.insert(_b[i]);
            chkmax(mindmg, (a[i] - 1) / b[i] + 1);
        }
        i64 res = 0;
        if (excrt(n, res))
            printf("%lld\n", res);
        else
            puts("-1");
    __end_kase:;
        all_b.clear();
        mindmg = 0;
    }
FINISHED:
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time used: " << clock() - _CLOCK_ST << std::endl;
#endif
    return 0;
}