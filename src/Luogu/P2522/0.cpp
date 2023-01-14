#include <bits/stdc++.h>
using namespace std;
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
  x = 0;
  char ch = getc();
  while (!isdigit(ch)) { ch = getc(); }
  while (isdigit(ch)) {
    x = x * 10 + ch - 48;
    ch = getc();
  }
  read(oth...);
}
void flush() { fwrite(buf2, 1, p3 + 1, stdout), p3 = -1; }
template <typename T, typename... T2>
void print(T x, T2... oth) {
  if (p3 > 1 << 20) flush();
  do { a[++p] = x % 10 + 48; } while (x /= 10);
  do { buf2[++p3] = a[p]; } while (--p);
  buf2[++p3] = hh;
  print(oth...);
}
}  // namespace FastIO
using FastIO::print;
using FastIO::read;
const int N = 5e4 + 5;
int prime[N], cnt;
bool vis[N];
int smu[N];
void seive(int n = N - 5) {
  smu[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!vis[i]) smu[prime[++cnt] = i] = -1;
    for (int j = 1; j <= cnt && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      if (i % prime[j] == 0) break;
      smu[i * prime[j]] = -smu[i];
    }
  }
  for (int i = 2; i <= n; ++i) smu[i] += smu[i - 1];
}
int calc(int m, int n, int k) {
  if (m > n) swap(m, n);
  int ans = 0;
  for (int l = 1, r; l <= m; l = r + 1) {
    r = min(n / (n / l), m / (m / l));
    ans += 1ll * (n / l / k) * (m / l / k) * (smu[r] - smu[l - 1]);
  }
  return ans;
}
int main() {
  seive();
  int _t;
  read(_t);
  int x, y, m, n, k;
  while (_t--) {
    read(x, m, y, n, k);
    print(calc(m, n, k) - calc(m, y - 1, k) - calc(x - 1, n, k) +
          calc(x - 1, y - 1, k));
  }
  FastIO::flush();
}
