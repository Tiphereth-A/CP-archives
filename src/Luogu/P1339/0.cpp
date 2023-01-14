#include <bits/stdc++.h>
using namespace std;
int hea[620001], ceg, d[600021], v[620001];
int n, m, s, e;
priority_queue<pair<int, int>> q;
struct Edge {
  int next, to, dis;
} edge[620001];
void add(int x, int y, int z) {
  edge[++ceg].next = hea[x];
  edge[ceg].to = y;
  edge[ceg].dis = z;
  hea[x] = ceg;
}
int main() {
  scanf("%d%d%d%d", &n, &m, &s, &e);
  for (int i = 1; i <= m; i++) {
    int x, y, z;
    scanf("%d%d%d", &x, &y, &z);
    add(x, y, z);
    add(y, x, z);
  }
  memset(d, 0x3f, sizeof(d));
  memset(v, 0, sizeof(v));
  d[s] = 0;
  q.push(make_pair(0, s));
  while (!q.empty()) {
    int x = q.top().second;
    q.pop();
    if (v[x]) continue;
    v[x] = 1;
    for (int i = hea[x]; i; i = edge[i].next) {
      int y = edge[i].to;
      if (d[y] > d[x] + edge[i].dis) {
        d[y] = d[x] + edge[i].dis;
        q.push(make_pair(-d[y], y));
      }
    }
  }
  printf("%d", d[e]);
  return 0;
}
