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
const int N = 5e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
const int MOD = 1e5 + 3;
const db EPS = 1e-6;
const int INF = 0x3f3f3f3f;
const i64 INFLL = 0x3f3f3f3f3f3f3f3f;
const db PI = acos(-1.0);
template <typename T = i64>
T qpow(T a, T b, T mod = MOD) {
    T res = 1;
    for (; b; b >>= 1, (a *= a) %= mod)
        if (b & 1) (res *= a) %= mod;
    return res;
}
i64 frac[25] = {1};
int main() {
#ifdef _LOCAL_
    clock_t _CLOCK_ST = clock();
#endif
    _for(i, 1, 20) frac[i] = frac[i - 1] * i;
    int kase;
    scanf("%d", &kase);
    while (kase--) {
        int n;
        scanf("%d", &n);
        double ans = 1, f = -1;
        _for(i, 1, n) {
            ans += f / frac[i];
            f *= -1;
        }
        printf("%2.2lf%%\n", 100 * ans);
    __end_kase:;
    }
FINISHED:
#ifdef _LOCAL_
    std::cerr << "\n---\n"
              << "Time used: " << clock() - _CLOCK_ST << std::endl;
#endif
    return 0;
}