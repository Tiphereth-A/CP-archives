#include <bits/stdc++.h>
const long long INFLL = 0x3f3f3f3f3f3f3f3fLL;
int _w, _t;
using namespace std;
const int N = 3e3 + 5;
bool g[N][N];
struct node {
  int in, id;
  bool operator<(const node &rhs) const {
    return in == rhs.in ? id < rhs.id : in > rhs.in;
  }
} deg[N];
int n, m;
int ans[N];
void solve() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) deg[i].id = i;
  for (int i = 1, x, y; i <= m; ++i) {
    scanf("%d%d", &x, &y);
    g[x][y] = g[y][x] = 1;
    ++deg[x].in;
    ++deg[y].in;
  }
  sort(deg + 1, deg + n + 1);
  for (int i = 1; i <= n / 3; ++i) ans[i] = deg[i].id;
  sort(ans + 1, ans + n / 3 + 1);
  for (int i = 1; i <= n / 3; ++i) printf("%d%c", ans[i], " \n"[i == n / 3]);
}
int main() {
  solve();
  return 0;
}
