#include <bits/stdc++.h>
using u64 = uint64_t;
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define ls rt << 1
#define rs rt << 1 | 1
#define Mid int m = ((r - l) >> 1) + l
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
  do { c = gc(); } while (c < '0' || c > '9');
  x = 0;
  do {
    x = (x << 3) + (x << 1) + (c ^ 48);
    c = gc();
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
u64 sum[MAXN << 2], add[MAXN << 2], a[MAXN];
int n, m;
void PushUp(const int &rt) { sum[rt] = sum[ls] + sum[rs]; }
void PushDown(const int &rt, const int &ln, const int &rn) {
  add[ls] += add[rt];
  sum[ls] += add[rt] * ln;
  add[rs] += add[rt];
  sum[rs] += add[rt] * rn;
  add[rt] = 0;
}
void Build(const int &l, const int &r, const int &rt) {
  if (l == r) {
    sum[rt] = a[l];
    return;
  }
  Mid;
  Build(l, m, ls);
  Build(m + 1, r, rs);
  PushUp(rt);
}
int L, R;
void Update(const u64 &c, const int &l, const int &r, const int &rt) {
  if (L <= l && r <= R) {
    sum[rt] += c * (r - l + 1);
    add[rt] += c;
    return;
  }
  Mid;
  PushDown(rt, m - l + 1, r - m);
  if (L <= m) Update(c, l, m, ls);
  if (R > m) Update(c, m + 1, r, rs);
  PushUp(rt);
}
u64 Query(const int &l, const int &r, const int &rt) {
  u64 ans = 0;
  if (L <= l && r <= R) return sum[rt];
  Mid;
  PushDown(rt, m - l + 1, r - m);
  if (L <= m) ans += Query(l, m, ls);
  if (R > m) ans += Query(m + 1, r, rs);
  return ans;
}
int main() {
  read(n, m);
  _for(i, 1, n) read(a[i]);
  Build(1, n, 1);
  char o;
  u64 k;
  while (m--) {
    read(o, L, R);
    if (o & 1) {
      read(k);
      Update(k, 1, n, 1);
    } else printf("%llu\n", Query(1, n, 1));
  }
  return 0;
}
