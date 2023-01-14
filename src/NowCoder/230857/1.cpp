#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int mod = 998244353;
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
i64 dp[N][N][2];
int sz[N];
void dfs(int now, int fa) {
  sz[now] = dp[now][0][0] = 1;
  _for_graph(i, now) {
    if (to == fa) continue;
    dfs(to, now);
    for (int j = sz[now] / 2; j >= 0; j--) {
      for (int t = 0; t <= sz[to] / 2; t++) {
        if (t) {
          (dp[now][j + t][0] +=
           (dp[to][t][0] + dp[to][t][1]) * dp[now][j][0]) %= mod;
          (dp[now][j + t][1] +=
           (dp[to][t][0] + dp[to][t][1]) * dp[now][j][1]) %= mod;
        }
        (dp[now][j + t + 1][1] += dp[to][t][0] * dp[now][j][0]) %= mod;
      }
    }
    sz[now] += sz[to];
  }
}
i64 f[N], ans = 0;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n;
  cin >> n;
  for (int i = 1, x, y; i <= 2 * n - 1; i++) {
    cin >> x >> y;
    addEdge(x, y);
    addEdge(y, x);
  }
  dfs(1, 0);
  f[0] = 1;
  for (int i = 1; i <= n; i++) f[i] = f[i - 1] * (2 * i - 1) % mod;
  for (int i = 0; i <= n; i++)
    (ans += (i & 1 ? -1 : 1) * (dp[1][i][0] + dp[1][i][1]) * f[n - i]) %= mod;
  cout << (ans + mod) % mod;
  return 0;
}
