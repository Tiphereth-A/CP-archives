#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int N = 4e3 + 5, M = 1e4 + 5;
struct Edge {
  int to, next;
  Edge(int _to = 0, int _next = 0): to(_to), next(_next) {}
} e[M];
int head[N], cnt_edge;
void addEdge(int x, int y) {
  e[++cnt_edge] = Edge(y, head[x]);
  head[x] = cnt_edge;
}
#define _for_graph(i, now) \
  for (int i = head[now], to = e[i].to; i; to = e[i = e[i].next].to)
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _rfor(i, r, l, vals...)                                      \
  for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vals; \
       i >= i##end;                                                  \
       --i)
const int mod = 998244353;
i64 dp[N][N][2];
int sz[N];
void dfs(int now, int fa) {
  sz[now] = dp[now][0][0] = 1;
  _for_graph(i, now) {
    if (to == fa) continue;
    dfs(to, now);
    _rfor(j, sz[now] / 2, 0)
      _for(t, 0, sz[to] / 2) {
        if (t) {
          (dp[now][j + t][0] +=
           (dp[to][t][0] + dp[to][t][1]) * dp[now][j][0]) %= mod;
          (dp[now][j + t][1] +=
           (dp[to][t][0] + dp[to][t][1]) * dp[now][j][1]) %= mod;
        }
        (dp[now][j + t + 1][1] += dp[to][t][0] * dp[now][j][0]) %= mod;
      }
    sz[now] += sz[to];
  }
}
i64 f[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n;
  cin >> n;
  _for(i, 1, 2 * n - 1, x, y) {
    cin >> x >> y;
    addEdge(x, y);
    addEdge(y, x);
  }
  i64 ans = 0;
  dfs(1, 0);
  f[0] = 1;
  _for(i, 1, n) f[i] = f[i - 1] * (2 * i - 1) % mod;
  _for(i, 0, n, sign = 1) {
    (ans += sign * (dp[1][i][0] + dp[1][i][1]) * f[n - i]) %= mod;
    sign *= -1;
  }
  cout << (ans + mod) % mod;
  return 0;
}
