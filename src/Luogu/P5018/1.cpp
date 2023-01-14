#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
const int OFFSET = 5;
const int N = 1e6 + OFFSET;
struct Node {
  int l, r;
} son[N];
int v[N], sz[N];
void dfs(int now) {
  if (now == -1) return;
  dfs(son[now].l);
  dfs(son[now].r);
  sz[now] =
    (~son[now].l ? sz[son[now].l] : 0) + (~son[now].r ? sz[son[now].r] : 0) + 1;
}
bool chk(int l, int r) {
  if (l == -1 && r == -1) return 1;
  if (l == -1 || r == -1) return 0;
  if (v[l] == v[r] && chk(son[l].l, son[r].r) && chk(son[l].r, son[r].l))
    return 1;
  return 0;
}
int main() {
  int n;
  scanf("%d", &n);
  _for(i, 1, n) scanf("%d", v + i);
  _for(i, 1, n) scanf("%d%d", &son[i].l, &son[i].r);
  dfs(1);
  int ans = 0;
  _for(i, 1, n)
    if (chk(son[i].l, son[i].r)) ans = max(ans, sz[i]);
  printf("%d", ans);
  return 0;
}
