#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
using std::min;
const int N = 1500 + 5;
int n;
struct edge {
  int to, next;
} e[N << 1];
int head[N], cnt, root;
void add(int u, int v) {
  e[++cnt] = {v, head[u]};
  head[u] = cnt;
}
int f[N][2];
void dfs(int pos, int fa = -1) {
  f[pos][0] = 0;
  f[pos][1] = 1;
  for (int i = head[pos]; i; i = e[i].next) {
    int v = e[i].to;
    if (v == fa) continue;
    dfs(v, pos);
    f[pos][0] += f[v][1];
    f[pos][1] += min(f[v][0], f[v][1]);
  }
}
int main() {
  cin >> n;
  for (int i = 1, x, k; i <= n; ++i) {
    cin >> x >> k;
    for (int j = 1, y; j <= k; ++j) {
      cin >> y;
      add(x, y);
      add(y, x);
    }
  }
  dfs(0);
  cout << min(f[0][0], f[0][1]);
  return 0;
}
