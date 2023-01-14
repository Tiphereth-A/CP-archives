#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2000 + 7, Mod = 1000000000 + 7;
vector<int> E[N];
int A[N], B[N], C[N], P[N], Q[N], Fa[N], S, sz[N];
int f[N][N][2];
int KSM(int x, int p) {
  int Ret = 1;
  while (p) {
    if (p & 1) (Ret *= x) %= Mod;
    p >>= 1, (x *= x) %= Mod;
  }
  return Ret;
}
void DP(int u, int fa) {
  sz[u] = 1;
  f[u][1][0] = 1;
  Fa[u] = fa;
  f[u][1][1] = A[u] * KSM(S, Mod - 2) % Mod;
  for (auto v : E[u]) {
    if (v == fa) continue;
    DP(v, u);
    for (int i = sz[u]; i; --i) {
      for (int j = sz[v]; j; --j) {
        f[u][i + j][0] =
          (f[u][i + j][0] + f[u][i][0] * f[v][j][0] % Mod * P[v] % Mod) % Mod;
        f[u][i + j][1] =
          (f[u][i + j][1] + (f[u][i][0] * f[v][j][1] % Mod * P[u] % Mod +
                             f[u][i][1] * f[v][j][0] % Mod * P[v] % Mod) %
                              Mod) %
          Mod;
      }
      f[u][i][0] = f[u][i][0] * (1 - P[v] + Mod) % Mod;
      f[u][i][1] = f[u][i][1] * (1 - P[v] + Mod) % Mod;
    }
    sz[u] += sz[v];
  }
}
void solve() {
  int n;
  cin >> n;
  for (int i = 1, u, v; i < n; ++i) {
    cin >> u >> v;
    E[u].push_back(v), E[v].push_back(u);
  }
  for (int i = 1; i <= n; ++i) {
    cin >> A[i] >> B[i] >> C[i];
    S += A[i], P[i] = B[i] * KSM(C[i], Mod - 2) % Mod;
  }
  DP(1, 0);
  for (int i = 2; i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
      f[1][j][1] = (f[1][j][1] + f[i][j][1] * (1 - P[Fa[i]] + Mod) % Mod) % Mod;
    }
  for (int i = 1; i <= n; ++i) cout << f[1][i][1] << endl;
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int i_ = 0;
  int t_ = 0;
  cin >> t_;
  solve();
  return 0;
}
