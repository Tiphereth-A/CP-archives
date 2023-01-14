#include <bits/stdc++.h>
#define N 5005
#define INF 0x7fffffff
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
using namespace std;
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
template <typename A, typename B>
void read(A &a, B &b) {
  read(a), read(b);
}
template <typename A, typename B, typename C>
void read(A &a, B &b, C &c) {
  read(a), read(b), read(c);
}
template <typename A, typename B, typename C, typename D>
void read(A &a, B &b, C &c, D &d) {
  read(a), read(b), read(c), read(d);
}
int g[N][N], ans, minn, v2[N];
bool v1[N];
int main() {
  int n, m;
  read(n, m);
  _for(i, 1, n)
    _for(j, 1, n) g[i][j] = INF;
  _for(i, 1, m) {
    int x, y, z;
    read(x, y, z);
    if (g[x][y] > z) g[x][y] = g[y][x] = z;
  }
  _for(i, 1, n) v2[i] = g[1][i];
  v1[1] = 1;
  int tot = 1, now = 0;
  while (tot < n) {
    minn = INF;
    tot++;
    _for(i, 1, n)
      if (!v1[i] && v2[i] < minn) {
        minn = v2[i];
        now = i;
      }
    ans += minn;
    _for(i, 1, n) {
      if (!v1[now] && v2[i] > g[now][i]) v2[i] = g[now][i];
    }
    v1[now] = 1;
  }
  _for(i, 1, n)
    if (v1[i] == 0) {
      printf("orz");
      return 0;
    }
  printf("%d", ans);
  return 0;
}
