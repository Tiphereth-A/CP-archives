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
const int N = 1e6 + 5;
int root[N << 5];
int n, m, a[N];
struct Persistable_Segment_Tree {
  int cnt_node;
  struct node {
    int n, l, r;
  } tr[N << 5];
#define PRE tr[pre]
#define NOW tr[now]
  void init(int l, int r, int &now) {
    now = ++cnt_node;
    if (l == r) {
      tr[now].n = a[l];
      return;
    }
    int mid = l + ((r - l) >> 1);
    init(l, mid, NOW.l);
    init(mid + 1, r, NOW.r);
  }
  void modify(int l, int r, int &now, int pre, int pos, int k) {
    tr[now = ++cnt_node] = PRE;
    if (l == r) {
      NOW.n = k;
      return;
    }
    int mid = l + ((r - l) >> 1);
    if (pos <= mid) modify(l, mid, NOW.l, PRE.l, pos, k);
    else modify(mid + 1, r, NOW.r, PRE.r, pos, k);
  }
  int query(int now, int l, int r, int pos) {
    if (l == r) return NOW.n;
    int mid = l + ((r - l) >> 1);
    if (pos <= mid) return query(NOW.l, l, mid, pos);
    else return query(NOW.r, mid + 1, r, pos);
  }
} T;
int main() {
  read(n, m);
  _for(i, 1, n) read(a[i]);
  T.init(1, n, root[0]);
  int v, op, loc, value;
  _for(i, 1, m) {
    read(v, op, loc);
    if (op & 1) {
      read(value);
      T.modify(1, n, root[i], root[v], loc, value);
    } else print(T.query(root[i] = root[v], 1, n, loc));
  }
  FastIO::flush();
  return 0;
}
