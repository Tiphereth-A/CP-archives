#include <bits/stdc++.h>
#define int long long
#define _for(p) for (signed i = head[p]; i; i = e[i].next)
const int N = 1e5 + 5;
int n, m, root, mod, val[N];
struct edge {
  int next, to;
} e[N * 2];
int head[N], cnt_edge;
void add_edge(int u, int v) {
  e[++cnt_edge] = {head[u], v};
  head[u] = cnt_edge;
}
int cnt;
int fa[N], dep[N], top[N], son[N], siz[N], rk[N], id[N];
void dfs1(int p, int father, int depth) {
  fa[p] = father;
  dep[p] = depth;
  siz[p] = 1;
  _for(p) {
    int v = e[i].to;
    if (v == father) continue;
    dfs1(v, p, depth + 1);
    siz[p] += siz[v];
    if (siz[son[p]] < siz[v]) son[p] = v;
  }
}
void dfs2(int p, int t) {
  top[p] = t;
  rk[++cnt] = p;
  id[p] = cnt;
  if (son[p]) dfs2(son[p], t);
  _for(p) {
    int v = e[i].to;
    if (v != fa[p] && v != son[p]) dfs2(v, v);
  }
}
namespace seg_tree {
#define now tree[p]
#define ls tree[p << 1]
#define rs tree[p << 1 | 1]
struct seg {
  int sum, lazy;
} tree[N * 4];
void push_up(int p) { now.sum = (ls.sum + rs.sum) % mod; }
void push_down(int p, int ln, int rn) {
  if (now.lazy) {
    (ls.lazy += now.lazy) %= mod;
    (ls.sum += now.lazy * ln) %= mod;
    (rs.lazy += now.lazy) %= mod;
    (rs.sum += now.lazy * rn) %= mod;
    now.lazy = 0;
  }
}
void build(int p, int l, int r) {
  if (l == r) {
    now.sum = val[rk[l]];
    return;
  }
  int mid = l + (r - l) / 2;
  build(p << 1, l, mid);
  build(p << 1 | 1, mid + 1, r);
  push_up(p);
}
void update(int p, int l, int r, int L, int R, int k) {
  if (L <= l && r <= R) {
    (now.sum += k * (r - l + 1)) %= mod;
    (now.lazy += k) %= mod;
    return;
  }
  int mid = l + (r - l) / 2;
  push_down(p, mid - l + 1, r - mid);
  if (L <= mid) update(p << 1, l, mid, L, R, k);
  if (mid < R) update(p << 1 | 1, mid + 1, r, L, R, k);
  push_up(p);
}
int query(int p, int l, int r, int L, int R) {
  if (L <= l && r <= R) return now.sum;
  int ans = 0;
  int mid = l + (r - l) / 2;
  push_down(p, mid - l + 1, r - mid);
  if (L <= mid) (ans += query(p << 1, l, mid, L, R)) %= mod;
  if (mid < R) (ans += query(p << 1 | 1, mid + 1, r, L, R)) %= mod;
  return ans % mod;
}
}  // namespace seg_tree
using namespace seg_tree;
void update2(int x, int y, int k) {
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) {
      update(1, 1, n, id[top[y]], id[y], k);
      y = fa[top[y]];
    } else {
      update(1, 1, n, id[top[x]], id[x], k);
      x = fa[top[x]];
    }
  }
  if (id[x] < id[y]) update(1, 1, n, id[x], id[y], k);
  else update(1, 1, n, id[y], id[x], k);
}
int query2(int x, int y) {
  int ans = 0;
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) {
      (ans += query(1, 1, n, id[top[y]], id[y])) %= mod;
      y = fa[top[y]];
    } else {
      (ans += query(1, 1, n, id[top[x]], id[x])) %= mod;
      x = fa[top[x]];
    }
  }
  if (id[x] < id[y]) (ans += query(1, 1, n, id[x], id[y])) %= mod;
  else (ans += query(1, 1, n, id[y], id[x])) %= mod;
  return ans % mod;
}
signed main() {
  scanf("%lld%lld%lld%lld", &n, &m, &root, &mod);
  for (int i = 1; i <= n; ++i) scanf("%lld", &val[i]);
  for (int u, v, i = 1; i < n; ++i) {
    scanf("%lld%lld", &u, &v);
    add_edge(u, v);
    add_edge(v, u);
  }
  dfs1(root, 0, 1);
  dfs2(root, root);
  build(1, 1, n);
  for (int op, x, y, z, i = 1; i <= m; ++i) {
    scanf("%lld", &op);
    switch (op) {
      case 1:
        scanf("%lld%lld%lld", &x, &y, &z);
        update2(x, y, z);
        break;
      case 2:
        scanf("%lld%lld", &x, &y);
        printf("%lld\n", query2(x, y));
        break;
      case 3:
        scanf("%lld%lld", &x, &z);
        update(1, 1, n, id[x], id[x] + siz[x] - 1, z);
        break;
      case 4:
        scanf("%lld", &x);
        printf("%lld\n", query(1, 1, n, id[x], id[x] + siz[x] - 1));
        break;
    }
  }
}
