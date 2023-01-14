#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using qi = queue<int>;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
#define _run_exit(expressions) _run_return(expressions, 0)
#define _run_return(expressions, val) return (expressions), val
#define _run_break(expressions) \
  {                             \
    expressions;                \
    break;                      \
  }
const int OFFSET = 5;
const int N = 1e4 + OFFSET;
bool g[N][N];
bool vis[N], valid[N];
int d[N];
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  int x, y;
  _for(i, 1, m) {
    scanf("%d%d", &x, &y);
    if (x != y) g[x][y] = 1;
  }
  scanf("%d%d", &x, &y);
  qi q;
  q.push(y);
  vis[y] = 1;
  while (!q.empty()) {
    int now = q.front();
    q.pop();
    _for(i, 1, n)
      if (!vis[i] && g[i][now]) {
        q.push(i);
        vis[i] = 1;
      }
  }
  if (!vis[x]) _run_exit(puts("-1"));
  _for(i, 1, n)
    if (vis[i]) {
      valid[i] = 1;
      _for(j, 1, n)
        if (g[i][j] && !vis[j]) _run_break(valid[i] = 0);
    }
  if (!valid[x]) _run_exit(puts("-1"));
  queue<pii> q2;
  q2.emplace(x, 0);
  while (!q2.empty()) {
    pii now = q2.front();
    q2.pop();
    if (now.first == y) _run_exit(printf("%d", now.second));
    _for(i, 1, n)
      if (g[now.first][i] && valid[i] && !d[i])
        q2.emplace(i, d[i] = now.second + 1);
  }
  puts("-1");
  return 0;
}
