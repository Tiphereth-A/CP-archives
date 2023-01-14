#include <bits/stdc++.h>
int fa[N], sum[N], num[N];
namespace fastIO {
template <typename A>
void read(A &x) {
  char c;
  A neg = 1;
  do { c = getchar(); } while ((c < '0' || c > '9') && c != '-');
  if (c == '-') neg = -1, c = getchar();
  x = 0;
  do {
    x = (x << 3) + (x << 1) + (c ^ 48);
    c = getchar();
  } while (c >= '0' && c <= '9');
  x *= neg;
}
template <typename A, typename... B>
void read(A &a, B &...b) {
  read(a), read(b...);
}
}  // namespace fastIO
int abs(int a) {
  int m = a >> 31;
  return (a + m) ^ m;
}
int find(int x) {
  if (x == fa[x]) return x;
  int fx = find(fa[x]);
  sum[x] += sum[fa[x]];
  return fa[x] = fx;
}
int main() {
  int t, x, y, fx, fy;
  fastIO::read(t);
  getchar();
  for (int i = 1; i <= 30000; ++i) {
    fa[i] = i;
    num[i] = 1;
  }
  char op;
  while (t--) {
    op = getchar();
    fastIO::read(x, y);
    getchar();
    fx = find(x);
    fy = find(y);
    if (op == 'M') {
      sum[fx] += num[fy];
      num[fy] += num[fx];
      num[fx] = 0;
      fa[fx] = fy;
    } else printf("%d\n", fx != fy ? -1 : abs(sum[x] - sum[y]) - 1);
  }
  return 0;
}
