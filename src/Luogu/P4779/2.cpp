#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _lch(p) ((p) << 1)
#define _rch(p) ((p) << 1 | 1)
#define _mid(l, r) (((l) + (r)) >> 1)
#define INF_I32 0x7fffffff
const int M = 500005;
const int N = 100005;
struct edge {
  int next, to, val;
} e[M];
int head[N], cnt;
void add(int u, int v, int val) {
  e[++cnt] = {head[u], v, val};
  head[u] = cnt;
}
int minPos[N << 2], minDis[N << 2];
void update(int pos) {
  if (minDis[_lch(pos)] < minDis[_rch(pos)]) {
    minDis[pos] = minDis[_lch(pos)];
    minPos[pos] = minPos[_lch(pos)];
  } else {
    minDis[pos] = minDis[_rch(pos)];
    minPos[pos] = minPos[_rch(pos)];
  }
}
void build(int cur, int l, int r, int s) {
  if (l == r) {
    minDis[cur] = (l == s) ? 0 : INF_I32;
    minPos[cur] = l;
    return;
  }
  int mid = _mid(l, r);
  build(_lch(cur), l, mid, s);
  build(_rch(cur), mid + 1, r, s);
  update(cur);
}
void modify(int cur, int l, int r, int pos, int k) {
  if (l == r) {
    minDis[cur] = k;
    return;
  }
  int mid = _mid(l, r);
  if (pos <= mid) modify(_lch(cur), l, mid, pos, k);
  else modify(_rch(cur), mid + 1, r, pos, k);
  update(cur);
}
int n, m, s, dis[N];
void dijkstra(int s) {
  build(1, 1, n, s);
  _for(i, 1, n) dis[i] = INF_I32;
  dis[s] = 0;
  while (minDis[1] < INF_I32) {
    int now = minPos[1];
    int valNow = dis[now];
    modify(1, 1, n, now, INF_I32);
    for (int i = head[now]; i; i = e[i].next) {
      int v = e[i].to, val = e[i].val;
      if (valNow + val < dis[v]) {
        dis[v] = valNow + val;
        modify(1, 1, n, v, valNow + val);
      }
    }
  }
  _for(i, 1, n) printf("%d ", dis[i]);
}
int main() {
  scanf("%d%d%d", &n, &m, &s);
  int u, v, w;
  _for(i, 1, m) {
    scanf("%d%d%d", &u, &v, &w);
    add(u, v, w);
  }
  dijkstra(s);
  return 0;
}
