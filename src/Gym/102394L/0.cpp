#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
const u64 MOD = 480903697910582ll;
const int N = 5e3 + 5;
namespace FastIO {
char buf[1 << 21], a[20], *p1 = buf, *p2 = buf;
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
}  // namespace FastIO
using FastIO::read;
int lists[N][N], tot_lis, lis_end;
u64 hashs[N][N];
int v[N], v_end;
int main() {
  int kase;
  read(kase);
  while (kase--) {
    tot_lis = lis_end = 0;
    int n, q;
    read(n, q);
    for (int i = 1, pre = -1, now = 0; i <= n; ++i) {
      read(now);
      if (now == pre) continue;
      int *lis = lists[++tot_lis];
      memcpy(lis, lists[tot_lis - 1], sizeof(lists[0][0]) * (n + 1));
      int pos = 0;
      for (int i = 1; i <= lis_end; ++i)
        if (lis[i] == now) {
          pos = i;
          break;
        }
      if (pos)
        for (int i = pos; i > 1; --i) lis[i] = lis[i - 1];
      else
        for (int i = ++lis_end; i > 1; --i) lis[i] = lis[i - 1];
      lis[1] = pre = now;
      for (int i = 1; i <= lis_end; ++i)
        hashs[tot_lis][i] = ((hashs[tot_lis][i - 1] + lis[i]) * n) % MOD;
    }
    for (int i = 1; i <= q; ++i) {
      v_end = 0;
      int len;
      read(len);
      for (int j = 1, _; j <= len; ++j) {
        read(_);
        if (_) v[++v_end] = _;
      }
      u64 hash2 = 0;
      for (int i = 1; i <= v_end; ++i) ((hash2 += v[i]) *= n) %= MOD;
      bool f = 0;
      for (int i = 1; i <= tot_lis; ++i)
        if (hash2 == hashs[i][v_end]) {
          bool f2 = 1;
          for (int j = 1; j <= v_end; ++j)
            if (v[j] != lists[i][j]) {
              f2 = 0;
              break;
            }
          if (f2) {
            f = 1;
            break;
          }
        }
      puts(f ? "Yes" : "No");
    }
  }
  return 0;
}
