#include <cctype>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int read() {
  int r, s = 0, c;
  for (; !isdigit(c = getchar()); s = c);
  for (r = c ^ 48; isdigit(c = getchar()); (r *= 10) += c ^ 48);
  return s ^ 45 ? r : -r;
}
const int M = 2100000, inf = 2e9 + 7;
int n, m, minn, t;
int _f(int x, int y, int pos) {
  int ans = (2 * m - 2) * (x - 1) + 2 * y - 1;
  if (pos == 2) ans++;
  return ans;
}
struct edge {
  int to, next, val;
} e[M << 2];
int head[M], cnt;
void addEdge(int u, int v, int val) {
  e[++cnt].next = head[u];
  e[cnt].to = v;
  e[cnt].val = val;
  head[u] = cnt;
}
struct node {
  int val, num;
  friend bool operator<(const node &a, const node &b) { return a.val > b.val; }
} f, ff;
int d[M];
bool vis[M];
void dijkstra(int s) {
  int num = 2 * n * m - 2 * n - 2 * m + 4;
  for (int i = 1; i <= num; i++) d[i] = inf, vis[i] = 0;
  priority_queue<node> q;
  f.num = s, f.val = 0;
  d[s] = 0;
  q.push(f);
  while (!q.empty()) {
    f = q.top();
    q.pop();
    if (vis[f.num]) continue;
    vis[f.num] = 1;
    for (int i = head[f.num]; i > 0; i = e[i].next) {
      int to = e[i].to;
      if (d[to] > d[f.num] + e[i].val) {
        d[to] = d[f.num] + e[i].val;
        ff.num = to, ff.val = d[to];
        q.push(ff);
      }
    }
  }
}
int main() {
  while (1) {
    minn = inf;
    n = read(), m = read();
    if (n == 0 || m == 0) return 0;
    memset(e, 0, sizeof(e));
    memset(head, 0, sizeof(head));
    cnt = 0;
    int val;
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j < m; ++j) {
        val = read();
        minn = min(minn, val);
        if (i == 1) addEdge(_f(i, j, 2), 2 * n * m - 2 * n - 2 * m + 4, val);
        else if (i == n)
          addEdge(2 * n * m - 2 * n - 2 * m + 3, _f(i - 1, j, 1), val);
        else
          addEdge(_f(i - 1, j, 1), _f(i, j, 2), val),
            addEdge(_f(i, j, 2), _f(i - 1, j, 1), val);
      }
    for (int i = 1; i < n; ++i)
      for (int j = 1; j <= m; ++j) {
        val = read();
        minn = min(minn, val);
        if (j == 1) addEdge(2 * n * m - 2 * n - 2 * m + 3, _f(i, j, 1), val);
        else if (j == m)
          addEdge(_f(i, j - 1, 2), 2 * n * m - 2 * n - 2 * m + 4, val);
        else
          addEdge(_f(i, j - 1, 2), _f(i, j, 1), val),
            addEdge(_f(i, j, 1), _f(i, j - 1, 2), val);
      }
    for (int i = 1; i < n; ++i)
      for (int j = 1; j < m; ++j) {
        val = read();
        minn = min(minn, val);
        addEdge(_f(i, j, 1), _f(i, j, 2), val),
          addEdge(_f(i, j, 2), _f(i, j, 1), val);
      }
    if (n == 1 || m == 1) {
      printf("%d\n", minn);
      return 0;
    }
    dijkstra(2 * n * m - 2 * n - 2 * m + 3);
    printf("Case %d: Minimum = %d\n", ++t, d[2 * n * m - 2 * n - 2 * m + 4]);
  }
  return 0;
}
