#include <bits/stdc++.h>
using u64 = uint64_t;
#define _for(i, l, r) for (unsigned long long i = (l); i <= (r); ++i)
#define lowbit(x) ((x) & -(x))
#define MAXN 100005
#define MAXBUF 140000000
char gc() {
  static char buf[MAXBUF], *p1 = buf, *p2 = buf;
  return p1 == p2 &&
             (p2 = (p1 = buf) + fread(buf, 1, MAXBUF, stdin), p1 == p2) ?
           EOF :
           *p1++;
}
template <typename A>
void read(A &x) {
  char c;
  do { c = getchar(); } while (c < '0' || c > '9');
  x = 0;
  do {
    x = (x << 3) + (x << 1) + (c ^ 48);
    c = getchar();
  } while (c >= '0' && c <= '9');
}
template <typename A, typename B>
void read(A &a, B &b) {
  read(a);
  read(b);
}
template <typename A, typename B, typename C>
void read(A &a, B &b, C &c) {
  read(a);
  read(b);
  read(c);
}
u64 n, m, c1[MAXN], c2[MAXN], num[MAXN];
void add(u64 *r, u64 pos, const u64 &v) {
  for (; pos <= n; pos += lowbit(pos)) r[pos] += v;
}
u64 query(u64 *r, u64 pos) {
  u64 ans(0);
  for (; pos; pos -= lowbit(pos)) ans += r[pos];
  return ans;
}
int main() {
  u64 op, x, y, k, sum1, sum2;
  read(n, m);
  _for(i, 1, n) {
    read(num[i]);
    add(c1, i, num[i] - num[i - 1]);
    add(c2, i, (i - 1) * (num[i] - num[i - 1]));
  }
  while (m--) {
    read(op, x, y);
    if (op & 1) {
      read(k);
      add(c1, x, k);
      add(c1, y + 1, -k);
      add(c2, x, k * (x - 1));
      add(c2, y + 1, -k * y);
    } else {
      sum1 = (x - 1) * query(c1, x - 1) - query(c2, x - 1);
      sum2 = y * query(c1, y) - query(c2, y);
      printf("%llu\n", sum2 - sum1);
    }
  }
  return 0;
}
