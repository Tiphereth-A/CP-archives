#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
#define _run_exit(expressions) _run_return(expressions, 0)
#define _run_return(expressions, val) return (expressions), val
#define _run_break(expressions) \
  {                             \
    expressions;                \
    break;                      \
  }
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const int OFFSET = 5;
const int N = 1 << 8, M = N * N + OFFSET, K = 21;
bool g[N][N];
char ans[M];
int n;
void dfs(int now) {
  _for(i, 0, N - 1)
    if (g[now][i]) {
      g[now][i] = g[i][now] = 0;
      dfs(i);
    }
  ans[n--] = now;
}
int d[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  char x, y;
  _for(i, 1, n) {
    cin >> x >> y;
    g[x][y] = g[y][x] = 1;
    ++d[x];
    ++d[y];
  }
  int cnt = 0, start = 0;
  _for(i, 0, N - 1)
    if (d[i] & 1) {
      ++cnt;
      if (!start) start = i;
    }
  if (cnt && cnt != 2) _run_exit(cout << "No Solution\n");
  if (!start)
    _for(i, 0, N - 1)
      if (d[i]) _run_break(start = i);
  dfs(start);
  cout << ans << '\n';
FINISHED:
  return 0;
}
