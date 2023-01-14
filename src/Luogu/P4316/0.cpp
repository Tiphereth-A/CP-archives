#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5, M = 4e5 + 5;
struct Edge {
  int w, to, next;
} e[M];
int head[N], cnt_edge;
int in[N], cnt[N];
void addEdge(int x, int y, int w = 1) {
  e[++cnt_edge] = {w, y, head[x]};
  head[x] = cnt_edge;
  ++in[y];
  ++cnt[y];
}
double f[N];
queue<int> q;
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1, u, v, w; i <= m + 1; ++i) {
    scanf("%d%d%d", &u, &v, &w);
    addEdge(v, u, w);
  }
  q.push(n);
  while (!q.empty()) {
    int now = q.front();
    q.pop();
    for (int i = head[now], to; i; i = e[i].next) {
      to = e[i].to;
      f[to] += (f[now] + e[i].w) / in[to];
      if (!(--cnt[to])) q.push(to);
    }
  }
  printf("%.2f", f[1]);
  return 0;
}
