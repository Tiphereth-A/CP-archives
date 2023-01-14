#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _lowbit(x) (1 << __builtin_ctz(x))
typedef long long ll;
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
typedef long long ll;
const int N = 1e6 + 5;
int n, m;
i64 a[N], tr[N], pos[N];
struct node {
  int l, r, id;
  i64 ans;
} q[N];
void add(int pos, int k) {
  for (; pos <= n; pos += _lowbit(pos)) tr[pos] += k;
}
i64 query(int pos) {
  i64 ans = 0;
  for (; pos; pos -= _lowbit(pos)) ans += tr[pos];
  return ans;
}
int main() {
  read(n);
  _for(i, 1, n) read(a[i]);
  read(m);
  _for(i, 1, m) {
    read(q[i].l, q[i].r);
    q[i].id = i;
  }
  std::sort(
    q + 1, q + m + 1, [](const node &a, const node &b) { return a.r < b.r; });
  int now_r = 0, tmp = 0;
  _for(i, 1, m) {
    if (q[i].r > now_r) {
      _for(j, now_r + 1, q[i].r) {
        if (pos[a[j]]) add(pos[a[j]], -1);
        add(pos[a[j]] = j, 1);
      }
      tmp = query(q[i].r);
      now_r = q[i].r;
    }
    q[i].ans = tmp - query(q[i].l - 1);
  }
  std::sort(
    q + 1, q + m + 1, [](const node &a, const node &b) { return a.id < b.id; });
  _for(i, 1, m) print(q[i].ans);
ex:
  FastIO::flush();
  return 0;
}
