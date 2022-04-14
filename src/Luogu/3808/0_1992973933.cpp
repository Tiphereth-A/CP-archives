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
const int N = 1e6 + OFFSET, M = 2e5 + OFFSET, K = 21;
const int MOD = 1e9 + 7;
const db EPS = 1e-6;
const int INF = 0x3f3f3f3f;
const i64 INFLL = 0x3f3f3f3f3f3f3f3f;
const db PI = acos(-1.0);
template <typename _T = std::ptrdiff_t, const char _str_begin = 'a', const char _str_end = 'z' + 1, std::size_t _N = N, bool _clear = false>
class ACAM {
  private:
    struct ACAM_t {
        std::size_t alpha[_str_end - _str_begin];
        std::size_t fail;
        bool end;
    };
    std::size_t cnt_nodes;
    bool builded;
    ACAM_t data[_N];
    _T e[_N];
    void _insert_end(std::size_t p, std::size_t x) { ++e[p]; }
    void _query_mid(_T &res, std::size_t p) {
        for (std::size_t i = p; i && ~e[i]; i = data[i].fail) {
            res += e[i];
            e[i] = -1;
        }
    };
    void _query_end(_T &res){};

  public:
    ACAM() {
        cnt_nodes = builded = 0;
        if (_clear) memset(data, 0, sizeof(data));
    }
    void clear() {
        cnt_nodes = builded = 0;
        memset(data, 0, sizeof(data));
    }
    void insert(const std::string &str, std::size_t x = 0) {
        std::size_t p = 0;
        for (std::size_t i = 0, c; i < str.size(); ++i) {
            if (!data[p].alpha[c = str[i] - _str_begin]) data[p].alpha[c] = ++cnt_nodes;
            p = data[p].alpha[c];
        }
        data[p].end = true;
        _insert_end(p, x);
    }
    void build() {
        std::queue<std::size_t> q;
        for (std::size_t i : data[0].alpha)
            if (i) q.push(i);
        std::size_t p = 0;
        while (!q.empty()) {
            p = q.front();
            q.pop();
            for (std::size_t i = 0; i < _str_end - _str_begin; ++i) {
                if (data[p].alpha[i]) {
                    data[data[p].alpha[i]].fail = data[data[p].fail].alpha[i];
                    q.push(data[p].alpha[i]);
                } else
                    data[p].alpha[i] = data[data[p].fail].alpha[i];
            }
        }
        builded = true;
    }
    _T query(const std::string &str) {
        if (!builded) build();
        std::size_t p = 0;
        _T res = 0;
        for (char c : str) _query_mid(res, p = data[p].alpha[c - _str_begin]);
        _query_end(res);
        return res;
    }
};
ACAM<> acam;
int e[N];
int main() {
#ifndef ONLINE_JUDGE
    clock_t _CLOCK_ST = clock();
#endif
    int n;
    cin >> n;
    string str;
    while (n--) {
        cin >> str;
        acam.insert(str);
    }
    cin >> str;
    cout << acam.query(str);
FINISHED:
#ifndef ONLINE_JUDGE
    std::cerr << "\n---\n"
              << "Time used: " << clock() - _CLOCK_ST << std::endl;
#endif
    return 0;
}