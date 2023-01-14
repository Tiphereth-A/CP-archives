#include <bits/stdc++.h>*/
#include <bits/stdc++.h>
#define N 1001
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
using namespace std;
typedef double db;
template <typename A>
A Max(const A &x, const A &y) {
  return x > y ? x : y;
}
template <typename A>
A Min(const A &x, const A &y) {
  return x < y ? x : y;
}
template <typename A>
void Swap(A &x, A &y) {
  x ^= y, y ^= x, x ^= y;
}
template <typename A>
A Abs(const A &x) {
  return x > 0 ? x : -x;
}
db x[N], y[N], d[N][N], ans = 1234567890.0;
int n, v[N];
void dfs(int step, int now, db l) {
  if (l > ans) return;
  if (step == n) {
    ans = Min(ans, l);
    return;
  }
  _for(i, 1, n)
    if (!v[i]) {
      v[i] = 1;
      dfs(step + 1, i, l + d[now][i]);
      v[i] = 0;
    }
}
int main() {
  scanf("%d", &n);
  _for(i, 1, n) scanf("%lf%lf", &x[i], &y[i]);
  _for(i, 0, n)
    _for(j, 0, n)
      d[i][j] =
        sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
  dfs(0, 0, 0.0);
  printf("%.2lf", ans);
  return 0;
}
