#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _lch ((p) << 1)
#define _rch ((p) << 1 | 1)
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
  x ^= y ^= x ^= y;
}
template <typename A>
A Abs(const A &x) {
  return x > 0 ? x : -x;
}
template <typename A>
A Gcd(A x, A y) {
  return !y ? x : Gcd(y, x % y);
}
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
}  // namespace FastIO
#define read FastIO::read
#define print FastIO::print
const int N = 1e5 + 5;
int n, w, a[N], final[N];
int tr[N << 2];
void build(int p, int l, int r) {
  if (l == r) {
    tr[p] = final[l];
    return;
  }
  int mid = l + ((r - l) >> 1);
  build(_lch, l, mid);
  build(_rch, mid + 1, r);
  tr[p] = Max(tr[_lch], tr[_rch]);
}
int main() {
  read(n, w);
  if (w == 0) {
    print(0);
    goto end;
  }
  int x, b;
  _for(i, 1, n) {
    read(x, b);
    a[x] += b;
  }
  _for(i, 1, w) final[0] += a[i];
  _for(i, 1, n - w) final[i] = final[i - 1] + a[i + w] - a[i];
  build(1, 1, n - w);
  print(tr[1]);
end:
  FastIO::flush();
  return 0;
}
