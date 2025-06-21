#include <bits/stdc++.h>
namespace FastIO {
char buf[1 << 21], buf2[1 << 21], a[20], *p1 = buf, *p2 = buf, hh = '\n';
int p, p3 = -1;
int getc() {
  return p1 == p2 &&
             (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ?
           EOF :
           *p1++;
}
int read() {
  int ret = 0, f = 0;
  char ch = getc();
  while (!isdigit(ch)) {
    if (ch == '-') f = 1;
    ch = getc();
  }
  while (isdigit(ch)) {
    ret = ret * 10 + ch - 48;
    ch = getc();
  }
  return f ? -ret : ret;
}
void flush() { fwrite(buf2, 1, p3 + 1, stdout), p3 = -1; }
void print(int x) {
  if (p3 > 1 << 20) flush();
  if (x < 0) buf2[++p3] = 45, x = -x;
  do { a[++p] = x % 10 + 48; } while (x /= 10);
  do { buf2[++p3] = a[p]; } while (--p);
  buf2[++p3] = hh;
}
}  // namespace FastIO
#define read() FastIO::read()
#define print(x) FastIO::print(x)
#include <bits/stdc++.h>
const int MAXN = 2e5 + 5;
int a[MAXN];
std::vector<int> v;
int getid(int x) { return lower_bound(v.begin(), v.end(), x) - v.begin() + 1; }
struct Node {
  int l, r, sum;
} hjt[MAXN * 40];
int cnt, root[MAXN];
void insert(int l, int r, int pre, int &now, int p) {
  hjt[++cnt] = hjt[pre];
  now = cnt;
  hjt[now].sum++;
  if (l == r) return;
  int m = (l + r) >> 1;
  if (p <= m) insert(l, m, hjt[pre].l, hjt[now].l, p);
  else insert(m + 1, r, hjt[pre].r, hjt[now].r, p);
}
int query(int l, int r, int L, int R, int k) {
  if (l == r) return l;
  int m = (l + r) >> 1;
  int tmp = hjt[hjt[R].l].sum - hjt[hjt[L].l].sum;
  if (k <= tmp) return query(l, m, hjt[L].l, hjt[R].l, k);
  else return query(m + 1, r, hjt[L].r, hjt[R].r, k - tmp);
}
int main() {
  int n = read(), m = read();
  for (int i = 1; i <= n; i++) v.push_back(a[i] = read());
  std::sort(v.begin(), v.end());
  v.erase(std::unique(v.begin(), v.end()), v.end());
  for (int i = 1; i <= n; i++) insert(1, n, root[i - 1], root[i], getid(a[i]));
  while (m--) {
    int l = read(), r = read(), k = read();
    print(v[query(1, n, root[l - 1], root[r], k) - 1]);
  }
  FastIO::flush();
  return 0;
}
