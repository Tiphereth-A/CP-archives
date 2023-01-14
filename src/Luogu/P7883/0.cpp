#include <bits/stdc++.h>
using namespace std;
namespace FastIO {
char buf[1 << 21], *p1 = buf, *p2 = buf;
char getc() {
  return p1 == p2 &&
             (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ?
           EOF :
           *p1++;
}
void read() {}
template <class T>
void read(T &x) {
  int f = x = 0;
  char ch = getc();
  while (!isdigit(ch)) {
    if (ch == '-') f = 1;
    ch = getc();
  }
  while (isdigit(ch)) { x = x * 10 + ch - '0', ch = getc(); }
  if (f) x = -x;
}
template <typename T, typename... T2>
void read(T &x, T2 &...oth) {
  read(x);
  read(oth...);
}
}  // namespace FastIO
using FastIO::read;
const i64 INF = 1e18;
const int M = 4e5 + 1;
struct Node {
  i64 x, y;
} a[M], b[M];
bool less_x(const Node &a, const Node &b) { return a.x < b.x; }
bool less_y(const Node &a, const Node &b) { return a.y < b.y; }
i64 work(int l, int r) {
  if (l == r) return INF;
  int mid = (l + r) >> 1, now = 0;
  i64 d = min(work(l, mid), work(mid + 1, r));
  for (int i = l; i <= r; ++i)
    if ((a[mid].x - a[i].x) * (a[mid].x - a[i].x) < d) b[++now] = a[i];
  sort(b + 1, b + 1 + now, less_y);
  for (int i = 1; i < now; ++i)
    for (int j = i + 1; j <= now; ++j) {
      if ((b[j].y - b[i].y) * (b[j].y - b[i].y) >= d) break;
      d = min(d,
              (b[j].x - b[i].x) * (b[j].x - b[i].x) +
                (b[j].y - b[i].y) * (b[j].y - b[i].y));
    }
  return d;
}
int main() {
  int n;
  read(n);
  for (int i = 1; i <= n; ++i) read(a[i].x, a[i].y);
  sort(a + 1, a + 1 + n, less_x);
  printf("%lld", work(1, n));
  return 0;
}
