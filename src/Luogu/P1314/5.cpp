#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
template <typename A>
A Max(const A &x, const A &y) {
  return x > y ? x : y;
}
template <typename A>
A Min(const A &x, const A &y) {
  return x < y ? x : y;
}
template <typename A>
A Abs(const A &x) {
  return x > 0 ? x : -x;
}
template <typename A>
void read(A &x) {
  char c;
  do { c = getchar(); } while (!isdigit(c));
  x = 0;
  do {
    x = (x << 3) + (x << 1) + (c ^ 48);
    c = getchar();
  } while (isdigit(c));
}
template <typename A, typename B>
void read(A &a, B &b) {
  read(a), read(b);
}
template <typename A, typename B, typename C>
void read(A &a, B &b, C &c) {
  read(a), read(b), read(c);
}
#define N 200005
#define INF_I32 0x7FFFFFFF
#define INF_I64 0x7FFFFFFFFFFFFFFFll
int n, m, w[N], v[N], l[N], r[N];
i64 s, prew[N], prev[N], sum, y;
bool check(int num) {
  y = 0;
  _for(i, 1, n)
    if (w[i] >= num) {
      prew[i] = prew[i - 1] + 1;
      prev[i] = prev[i - 1] + v[i];
    } else {
      prew[i] = prew[i - 1];
      prev[i] = prev[i - 1];
    }
  int tmpl, tmpr;
  _for(i, 1, m) {
    tmpl = l[i] - 1;
    tmpr = r[i];
    y += (prew[tmpr] - prew[tmpl]) * (prev[tmpr] - prev[tmpl]);
  }
  sum = Abs(s - y);
  return y > s ? 1 : 0;
}
int main() {
  read(n, m, s);
  int L = INF_I32, R = -1, mid;
  i64 ans = INF_I64;
  _for(i, 1, n) {
    read(w[i], v[i]);
    R = Max(R, w[i]);
    L = Min(L, w[i]);
  }
  _for(i, 1, m) read(l[i], r[i]);
  L--;
  R += 2;
  while (L <= R) {
    mid = (L + R) >> 1;
    if (check(mid)) L = mid + 1;
    else R = mid - 1;
    if (sum < ans) ans = sum;
  }
  printf("%lld", ans);
  return 0;
}
