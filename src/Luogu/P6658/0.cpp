#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5, M = 1e6 + 5;
struct Edge {
  int to, next;
} e[M];
int head[N], cnt_edge = 1;
void addEdge(int x, int y) {
  e[++cnt_edge] = {y, head[x]};
  head[x] = cnt_edge;
}
#define _for_graph(head, e, i, now) \
  for (int i = head[now], v = e[i].to; i; v = e[i = e[i].next].to)
namespace union_find {
int par[N];
void init() { memset(par, 0xff, sizeof par); }
int find(int x) { return par[x] < 0 ? x : par[x] = find(par[x]); }
void merge(int u, int v) {
  int p = find(u), q = find(v);
  if (p == q) return;
  par[p] += par[q];
  par[q] = p;
}
};  // namespace union_find
int n, m;
namespace two_edge_connect {
int low[N], dfn[N], dfc;
int stk[N], tp;
int bel[N], s;
void dfs(int u, int fa) {
  low[u] = dfn[u] = ++dfc;
  stk[++tp] = u;
  _for_graph(head, e, i, u) {
    if ((i ^ fa) == 1) continue;
    if (dfn[v] == 0) {
      dfs(v, i);
      low[u] = min(low[u], low[v]);
    } else low[u] = min(low[u], dfn[v]);
  }
  if (low[u] == dfn[u]) {
    s++;
    for (;;) {
      int v = stk[tp--];
      bel[v] = s;
      if (u == v) break;
    }
  }
}
void init() {
  for (int i = 1; i <= n; ++i)
    if (dfn[i] == 0) dfs(i, 0);
}
bool isbridge(int u, int v) { return bel[u] != bel[v]; }
};  // namespace two_edge_connect
namespace three_edge_connect {
using two_edge_connect::isbridge;
using union_find::find;
using union_find::merge;
int low[N], dfn[N], end[N], dfc;
int deg[N];
bool insubtree(int u, int v) { return (dfn[u] <= dfn[v] && dfn[v] <= end[u]); }
void absorb(vector<int> &path, int u, int w = 0) {
  while (path.empty() == false) {
    int v = path.back();
    if (w > 0 && insubtree(v, w) == false) break;
    path.pop_back();
    deg[u] += deg[v] - 2;
    merge(u, v);
  }
}
void dfs(int u, int fa, vector<int> &pu) {
  low[u] = dfn[u] = ++dfc;
  _for_graph(head, e, i, u) {
    if (u == v || isbridge(u, v) == true) continue;
    deg[u]++;
    if ((i ^ fa) == 1) continue;
    if (dfn[v] == 0) {
      vector<int> pv;
      dfs(v, i, pv);
      if (deg[v] == 2) pv.pop_back();
      if (low[v] < low[u]) {
        low[u] = low[v];
        absorb(pu, u);
        pu = pv;
      } else absorb(pv, u);
    } else {
      if (dfn[v] > dfn[u]) {
        absorb(pu, u, v);
        deg[u] -= 2;
      } else if (dfn[v] < low[u]) {
        low[u] = dfn[v];
        absorb(pu, u);
      }
    }
  }
  end[u] = dfc;
  pu.push_back(u);
}
void init() {
  union_find::init();
  two_edge_connect::init();
  for (int i = 1; i <= n; ++i)
    if (dfn[i] == 0) {
      vector<int> pi;
      dfs(i, 0, pi);
    }
}
vector<vector<int>> get_all() {
  vector<vector<int>> res(n), ans;
  for (int i = 1; i <= n; ++i) {
    int x = find(i);
    res[x - 1].push_back(i);
  }
  for (int i = 0; i < n; ++i)
    if (!res[i].empty()) ans.push_back(res[i]);
  return ans;
}
};  // namespace three_edge_connect
void init() {
  cin >> n >> m;
  for (int i = 1, u, v; i <= m; ++i) {
    cin >> u >> v;
    addEdge(u, v);
    addEdge(v, u);
  }
}
bool cmp(const vector<int> &x, const vector<int> &y) { return x[0] < y[0]; }
void solve() {
  using three_edge_connect::get_all;
  three_edge_connect::init();
  vector<vector<int>> ans = get_all();
  for (int i = 0; i < ans.size(); ++i) sort(ans[i].begin(), ans[i].end());
  sort(ans.begin(), ans.end(), cmp);
  cout << ans.size() << '\n';
  for (int i = 0, s; i < ans.size(); ++i) {
    s = ans[i].size();
    for (int j = 0; j < s; ++j) cout << ans[i][j] << " \n"[j == s - 1];
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  init();
  solve();
  return 0;
}
