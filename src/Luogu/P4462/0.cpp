#include <bits/stdc++.h>
#define _for(i, l, r) for (auto i = (l); i <= (r); ++i)
namespace FastIO {
char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf, hh = '\n';
int p, p3 = -1;
int getc() {
  return p1 == p2 &&
             (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ?
           EOF :
           *p1++;
}
void read() {}
void print() {}
template <typename T, typename... T2>
void read(T &x, T2 &...oth) {
  int f = 0;
  x = 0;
  char ch = getc();
  while (!isdigit(ch)) {
    if (ch == '-') f = 1;
    ch = getc();
  }
  while (isdigit(ch)) {
    x = x * 10 + ch - 48;
    ch = getc();
  }
  if (f) x = -x;
  read(oth...);
}
void flush() { fwrite(buf2, 1, p3 + 1, stdout), p3 = -1; }
template <typename T, typename... T2>
void print(T x, T2... oth) {
  if (p3 > 1 << 20) flush();
  if (x < 0) buf2[++p3] = 45, x = -x;
  do { a[++p] = x % 10 + 48; } while (x /= 10);
  do { buf2[++p3] = a[p]; } while (--p);
  buf2[++p3] = hh;
  print(oth...);
}
template <typename T>
void print_h(T x, char h) {
  if (p3 > 1 << 20) flush();
  if (x < 0) buf2[++p3] = 45, x = -x;
  do { a[++p] = x % 10 + 48; } while (x /= 10);
  do { buf2[++p3] = a[p]; } while (--p);
  buf2[++p3] = h;
}
void putchar(char a) { buf2[++p3] = a; }
}  // namespace FastIO
using FastIO::print;
using FastIO::read;
const int M = 2e5 + 5;
const int N = 1e5 + 5;
int n, m, sqrt_n, blocks[N];
i64 k;
i64 xor_num[N];
struct query_node {
  int l, r, id;
  bool operator<(const query_node &other) const {
    return (blocks[l] != blocks[other.l]) ? l < other.l :
                                            (r > other.r) ^ (blocks[l] & 1);
  }
} query[N];
i64 ans[N];
namespace mo {
i64 cnt[M];
i64 add(int p) {
  i64 ans = cnt[xor_num[p] ^ k];
  ++cnt[xor_num[p]];
  return ans;
}
i64 del(int p) {
  --cnt[xor_num[p]];
  return cnt[xor_num[p] ^ k];
}
}  // namespace mo
using mo::add;
using mo::del;
int main() {
  read(n, m, k);
  sqrt_n = sqrt(n);
  _for(i, 1, n) blocks[i] = (i - 1) / sqrt_n + 1;
  _for(i, 1, n) {
    read(xor_num[i]);
    xor_num[i] ^= xor_num[i - 1];
  }
  for (int i = 1, l, r; i <= m; ++i) {
    read(l, r);
    query[i] = {l - 1, r, i};
  }
  std::sort(query + 1, query + m + 1);
  int l = 1, r = 0;
  i64 now_ans = 0;
  _for(i, 1, m) {
    int now_l = query[i].l, now_r = query[i].r;
    while (l < now_l) now_ans -= del(l++);
    while (l > now_l) now_ans += add(--l);
    while (r < now_r) now_ans += add(++r);
    while (r > now_r) now_ans -= del(r--);
    ans[query[i].id] = now_ans;
  }
  _for(i, 1, m) print(ans[i]);
  FastIO::flush();
  return 0;
}
