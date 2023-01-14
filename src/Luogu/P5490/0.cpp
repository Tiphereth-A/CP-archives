#include <bits/stdc++.h>
const int N = 2e5 + 5;
struct node_sgt {
  int l, r;
  int lc, rc;
  int cover;
  unsigned long long len;
} slen[N << 3];
int cnt_sgt = 1;
#define _now slen[p]
#define _lch slen[slen[p].lc]
#define _rch slen[slen[p].rc]
struct edge {
  int x, y1, y2;
  int state;
  bool operator<(const edge &oth) const { return x < oth.x; }
} line[N];
int v[N];
unsigned long long ans;
int n;
void pushup(int p) {
  _now.len = (_now.cover) ? _now.r - _now.l : _lch.len + _rch.len;
}
void build(int l, int r, int p = 1) {
  _now.l = v[l];
  _now.r = v[r];
  if (r - l <= 1) return;
  int mid = l + ((r - l) >> 1);
  build(l, mid, _now.lc = ++cnt_sgt);
  build(mid, r, _now.rc = ++cnt_sgt);
}
void modify(int x, int y, int state, int p = 1) {
  if (!p) return;
  int l = _now.l, r = _now.r;
  if (x <= l && r <= y) {
    _now.cover += state;
    pushup(p);
    return;
  }
  if (x < _lch.r) modify(x, y, state, _now.lc);
  if (_rch.l < y) modify(x, y, state, _now.rc);
  pushup(p);
}
int main() {
  scanf("%d", &n);
  int x1, x2, y1, y2;
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    line[i] = (edge){x1, y1, y2, 1};
    v[i] = y1;
    line[i + n] = (edge){x2, y1, y2, -1};
    v[i + n] = y2;
  }
  std::sort(v + 1, v + 1 + n * 2);
  std::sort(line + 1, line + 1 + n * 2);
  build(1, n * 2);
  for (int i = 1; i <= n * 2; ++i) {
    ans += slen[1].len * (line[i].x - line[i - 1].x);
    modify(line[i].y1, line[i].y2, line[i].state);
  }
  printf("%llu", ans);
  return 0;
}
