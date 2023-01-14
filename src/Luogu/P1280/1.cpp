#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _rfor(i, r, l) for (int i = (r); i >= (l); --i)
template <typename A>
A Max(const A &x, const A &y) {
  return x > y ? x : y;
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
const int M = 10005;
struct task {
  int st, t;
} a[M];
int n, k, sum[M], now = 1, f[M];
bool cmp(task a, task b) { return a.st > b.st; }
int main() {
  read(n, k);
  _for(i, 1, k) {
    read(a[i].st, a[i].t);
    sum[a[i].st]++;
  }
  std::sort(a + 1, a + k + 1, cmp);
  _rfor(i, n, 1) {
    if (sum[i])
      _for(j, 1, sum[i]) {
        f[i] = Max(f[i], f[i + a[now].t]);
        now++;
      }
    else f[i] = f[i + 1] + 1;
  }
  printf("%d", f[1]);
  return 0;
}
