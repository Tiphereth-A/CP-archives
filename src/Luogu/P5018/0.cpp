#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const int OFFSET = 5;
const int N = 1e6 + OFFSET, M = 2e5 + OFFSET, K = 21;
struct Node {
  int l, r;
} son[N];
int v[N];
u64 hash1[N], hash2[N], p = 1001;
int sz[N];
void dfs(int now) {
  if (now == -1) return;
  dfs(son[now].l);
  dfs(son[now].r);
  sz[now] = sz[son[now].l] + sz[son[now].r] + 1;
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
  int l, r;
  _for(i, 1, n) {
    scanf("%d%d", &l, &r);
    son[i].l = l;
    son[i].r = r;
  }
  dfs(1);
  int ans = 0;
  _for(i, 1, n)
    if (chk(son[i].l, son[i].r)) ans = max(ans, sz[i]);
  printf("%d", ans);
FINISHED:
  return 0;
}
