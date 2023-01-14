#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _rep(i, l, r) for (int i = (l); i < (r); ++i)
template <typename A>
A Max(const A &x, const A &y) {
  return x < y ? y : x;
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
char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf, hh = ' ';
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
namespace Seg {
#define _now tree[p]
#define _lch tree[p].l
#define _rch tree[p].r
struct node {
  int first, second, pos;
} pair[N];
struct segtree {
  node val;
  int l, r;
  bool operator<(const segtree &a) const {
    return (val.first == a.val.first) ? val.second < a.val.second :
                                        val.first < a.val.first;
  }
  void pt() { print(val.first, val.second); }
} tree[N << 2];
int cnt;
node _max(const segtree &a, const segtree &b) { return a < b ? b.val : a.val; }
void push_up(int p) { _now.val = _max(tree[_lch], tree[_rch]); }
void build(int &p, int l, int r) {
  p = ++cnt;
  if (l == r) {
    _now = {pair[l], 0, 0};
    return;
  }
  int mid = l + ((r - l) >> 1);
  build(_lch, l, mid);
  build(_rch, mid + 1, r);
  push_up(p);
}
void del(int p, int l, int r, int target) {
  if (_now.val.first == -1) return;
  if (l == r) {
    _now = {pair[target] = {-1, -1, target}, 0, 0};
    return;
  }
  int mid = l + ((r - l) >> 1);
  if (target <= mid) del(_lch, l, mid, target);
  else del(_rch, mid + 1, r, target);
  push_up(p);
}
void modify(int p, int l, int r, int target, const node &a) {
  if (l == r) {
    _now = {pair[target] = a, 0, 0};
    return;
  }
  int mid = l + ((r - l) >> 1);
  if (target <= mid) modify(_lch, l, mid, target, a);
  else modify(_rch, mid + 1, r, target, a);
  push_up(p);
}
}  // namespace Seg
struct list {
  int pre, suc;
} id[N];
int head, rear;
int a[N], n;
void del_rear(const int &p, const int &pre) {
  Seg::del(1, 1, n, p);
  Seg::del(1, 1, n, pre);
  rear = id[pre].pre;
  id[pre].pre = id[rear].suc = 0;
}
void del_head(const int &p, const int &suc) {
  Seg::del(1, 1, n, p);
  Seg::del(1, 1, n, suc);
  head = id[suc].suc;
  id[suc].suc = id[head].pre = 0;
}
void del(const int &p, const int &pre, const int &suc) {
  Seg::modify(1, 1, n, p, {Seg::pair[pre].first, Seg::pair[suc].second, p});
  Seg::del(1, 1, n, pre);
  if (!id[pre].pre) head = p;
  else id[id[pre].pre].suc = p;
  id[p].pre = id[pre].pre;
  Seg::del(1, 1, n, suc);
  if (!id[suc].suc) rear = p;
  else id[id[suc].suc].pre = p;
  id[p].suc = id[suc].suc;
}
int main() {
  read(n);
  _for(i, 1, n) read(a[i]);
  --n;
  _for(i, 1, n) {
    Seg::pair[i] = {a[i], a[i + 1], i};
    id[i] = {i - 1, i + 1};
  }
  int tmp1;
  head = 1;
  rear = n;
  id[n].suc = 0;
  Seg::build(tmp1, 1, n);
  _rep(i, 1, (n + 1) >> 1) {
    Seg::tree[1].pt();
    int tmp = Seg::tree[1].val.pos;
    int suc = id[tmp].suc, pre = id[tmp].pre;
    if (tmp == rear) del_rear(tmp, pre);
    else if (tmp == head) del_head(tmp, suc);
    else del(tmp, pre, suc);
  }
  Seg::tree[1].pt();
  --FastIO::p3;
  FastIO::flush();
  return 0;
}
