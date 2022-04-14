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
const int N = 3e5 + OFFSET, M = 1e6, K = 21;
const int MOD = 1e9 + 7;
const db EPS = 1e-6;
const int INF = 0x3f3f3f3f;
const i64 INFLL = 0x3f3f3f3f3f3f3f3f;
const db PI = acos(-1.0);
template <typename _T = std::ptrdiff_t, const std::size_t _N = N, const bool _clear = false>
class BIT {
  private:
    _T tree[_N];
    std::size_t lowbit(std::ptrdiff_t x) { return x & (-x); }

  public:
    BIT() {
        if (_clear) memset(tree, 0, sizeof(tree));
    }
    void clear() { memset(tree, 0, sizeof(tree)); }
    void add(std::size_t pos, _T val = 1) {
        for (std::size_t i = pos; i < _N; i += lowbit(i)) tree[i] += val;
    }
    _T query(std::size_t pos) {
        _T ret = 0;
        for (std::size_t i = pos; i; i = (std::ptrdiff_t)i - lowbit(i)) ret += tree[i];
        return ret;
    }
};
BIT<i64, N * 2> tr;
int fa[N];
int find(int x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
void merge(int x, int y) { fa[find(x)] = find(y); }
i64 d[M + OFFSET];
i64 a[N] = {0, 1, 2};
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    _for(i, 1, M)
        for (int j = i; j <= M; j += i) ++d[j];
    _for(i, 1, n) {
        fa[i] = i;
        scanf("%lld", a + i);
        tr.add(i, a[i]);
    }
    fa[n + 1] = n + 1;
    int op, l, r;
    _for(i, 1, m) {
        scanf("%d%d%d", &op, &l, &r);
        if (op == 1) {
            for (int i = l; i <= r; i = find(i) == i ? i + 1 : fa[i]) {
                tr.add(i, d[a[i]] - a[i]);
                if ((a[i] = d[a[i]]) <= 2) fa[i] = i + 1;
            }
        } else
            printf("%lld\n", tr.query(r) - tr.query(l - 1));
    }
    return 0;
}