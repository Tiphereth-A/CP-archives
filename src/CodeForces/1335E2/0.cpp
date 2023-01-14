#include <bits/stdc++.h>
#define _for(i, l, r) for (auto i = (l); i <= (r); ++i)
#define _set_nul(a) memset(a, 0, sizeof(a))
namespace FastIO {
void read() {}
template <typename T, typename... T2>
void read(T &x, T2 &...oth) {
  x = 0;
  char ch = getchar();
  while (!isdigit(ch)) { ch = getchar(); }
  while (isdigit(ch)) {
    x = x * 10 + ch - 48;
    ch = getchar();
  }
  read(oth...);
}
}  // namespace FastIO
using FastIO::read;
const int M = 200 + 1, N = 2e5 + 2;
int max(int x, int y) {
  int m = (x - y) >> 31;
  return x & ~m | y & m;
}
struct Edge {
  int to, next;
} e[N];
int head[M], cnt_edge;
void addEdge(int x, int y) {
  e[++cnt_edge] = {y, head[x]};
  head[x] = cnt_edge;
}
int a[N], sum[N][M], pos[N];
int main() {
  int kase;
  read(kase);
  while (kase--) {
    _set_nul(head);
    cnt_edge = 0;
    int n;
    read(n);
    _for(i, 1, n) {
      read(a[i]);
      addEdge(a[i], i);
      memcpy(sum[i], sum[i - 1], sizeof(sum[i]));
      ++sum[i][a[i]];
    }
    int ans = 1;
    _for(i, 1, 200) {
      int cnt_pos = 0;
      for (int j = head[i]; j; j = e[j].next) { pos[++cnt_pos] = e[j].to; }
      for (int j = 1, tmp; j <= cnt_pos / 2; ++j) {
        tmp = 0;
        _for(k, 1, 200) {
          tmp = max(tmp, sum[pos[j] - 1][k] - sum[pos[cnt_pos - j + 1]][k]);
        }
        ans = max(ans, j * 2 + tmp);
      }
    }
    printf("%d\n", ans);
  }
}
