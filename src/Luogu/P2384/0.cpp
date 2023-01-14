#include <cctype>
#include <cmath>
#include <cstdio>
#include <queue>
namespace fastIO {
#define tpn typename
template <tpn A>
void read(A &x) {
  char c;
  A neg = 1;
  do { c = getchar(); } while ((c < '0' || c > '9') && c != '-');
  if (c == '-') neg = -1, c = getchar();
  x = 0;
  do {
    x = (x << 3) + (x << 1) + (c ^ 48);
    c = getchar();
  } while (c >= '0' && c <= '9');
  x *= neg;
}
template <tpn A, tpn... B>
void read(A &a, B &...b) {
  read(a), read(b...);
}
}  // namespace fastIO
using namespace fastIO;
typedef long double ldb;
const int M = 1e6 + 5, N = 1e3 + 5;
int n, m;
struct edge {
  int next, to;
  int val;
} e[M];
struct path {
  int val, pre;
} pa[N];
int head[N], cnt_edge;
bool vis[N];
ldb dist[N];
std::queue<int> q;
void add(int u, int v, int w) {
  e[++cnt_edge] = {head[u], v, w};
  head[u] = cnt_edge;
}
void spfa() {
  vis[1] = true;
  for (int i = 2; i <= n; ++i) dist[i] = 1e12;
  q.push(1);
  while (!q.empty()) {
    int now = q.front();
    q.pop();
    for (int i = head[now]; i; i = e[i].next) {
      int to = e[i].to;
      ldb val = logl(e[i].val);
      if (dist[to] > dist[i] + val) {
        dist[to] = dist[i] + val;
        pa[to] = {e[i].val, now};
        if (!vis[to]) {
          vis[to] = true;
          q.push(to);
        }
      }
    }
  }
}
int main() {
  read(n, m);
  int x, y, z;
  for (int i = 1; i <= m; ++i) {
    read(x, y, z);
    add(x, y, z);
  }
  spfa();
  long long ans = 1;
  int pos = n;
  for (int pos = n; pos != 1; pos = pa[pos].pre) ans *= pa[pos].val;
  printf("%d", ans % 9987);
  return 0;
}
