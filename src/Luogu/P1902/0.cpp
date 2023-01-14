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
using FastIO::print_h;
using FastIO::read;
#define _for(i, l, r) for (auto i = (l); i <= (r); ++i)
const int N = 1005;
int max(int a, int b) {
  int m = (a - b) >> 31;
  return b & m | a & ~m;
}
int m, n;
int map[N][N], vis[N][N];
const int move[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
bool dfs(int x, int y, int dmg, int max_dmg) {
  if (x == n) return true;
  for (int i = 0; i < 4; ++i) {
    int xx = x + move[i][0], yy = y + move[i][1];
    if (xx > 0 && yy > 0 && xx <= n && yy <= m && vis[xx][yy] != max_dmg &&
        map[xx][yy] <= max_dmg) {
      vis[xx][yy] = max_dmg;
      if (dfs(xx, yy, max(dmg, map[xx][yy]), max_dmg)) return true;
    }
  }
  return false;
}
int main() {
  read(n, m);
  int l = 0, r = -1, mid;
  _for(i, 1, n)
    _for(j, 1, m) {
      read(map[i][j]);
      r = max(r, map[i][j]);
    }
  int ans = r;
  while (l <= r) {
    mid = (r - l) / 2 + l;
    if (dfs(1, 1, -1, mid)) r = (ans = mid) - 1;
    else l = mid + 1;
  }
  print(ans);
  FastIO::flush();
  return 0;
}
