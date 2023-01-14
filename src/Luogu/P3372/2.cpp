#include <bits/stdc++.h>
using u64 = uint64_t;
#define _for(i, l, r) for (unsigned long long i = (l); i <= (r); ++i)
#define ls rt << 1
#define rs rt << 1 | 1
#define Mid unsigned long long m = ((r - l) >> 1) + l
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
  read(a), read(b);
}
template <typename A, typename B, typename C>
void read(A &a, B &b, C &c) {
  read(a), read(b), read(c);
}
template <typename A>
void print(A x) {
  if (x > 9) _print(x / 10);
  putchar(x % 10 + '0');
}
u64 sum[MAXN << 2], add[MAXN << 2], a[MAXN];
void PushUp(const u64 &rt) { sum[rt] = sum[ls] + sum[rs]; }
void PushDown(const u64 &rt, const u64 &ln, const u64 &rn) {
  add[ls] += add[rt];
  sum[ls] += add[rt] * ln;
  add[rs] += add[rt];
  sum[rs] += add[rt] * rn;
  add[rt] = 0;
}
void Build(const u64 &l, const u64 &r, const u64 &rt) {
  if (l == r) {
    sum[rt] = a[l];
    return;
  }
  Mid;
  Build(l, m, ls);
  Build(m + 1, r, rs);
  PushUp(rt);
}
void Update(const u64 &L,
            const u64 &R,
            const u64 &c,
            const u64 &l,
            const u64 &r,
            const u64 &rt) {
  if (L <= l && r <= R) {
    sum[rt] += c * (r - l + 1);
    add[rt] += c;
    return;
  }
  Mid;
  PushDown(rt, m - l + 1, r - m);
  if (L <= m) Update(L, R, c, l, m, ls);
  if (R > m) Update(L, R, c, m + 1, r, rs);
  PushUp(rt);
}
u64 Query(
  const u64 &L, const u64 &R, const u64 &l, const u64 &r, const u64 &rt) {
  u64 ans = 0;
  if (L <= l && r <= R) return sum[rt];
  Mid;
  PushDown(rt, m - l + 1, r - m);
  if (L <= m) ans += Query(L, R, l, m, ls);
  if (R > m) ans += Query(L, R, m + 1, r, rs);
  return ans;
}
int main() {
  u64 n = 0, m = 0;
  read(n, m);
  _for(i, 1, n) read(a[i]);
  Build(1, n, 1);
  u64 o = 0, x = 0, y = 0, k = 0;
  while (m--) {
    read(o, x, y);
    if (o & 1) {
      read(k);
      Update(x, y, k, 1, n, 1);
    } else printf("%llu\n", Query(x, y, 1, n, 1));
  }
  return 0;
}
