#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, k;
int q[N];
struct E {
  int to, next;
} e[N * 2];
int tot, head[N * 2];
void addEdge(int u, int v) {
  e[tot] = {v, head[u]};
  head[u] = tot++;
}
int w[N * 2], c[N * 2];
bool ff[N * 2];
void dfs(int u) {
  c[u] = ff[u];
  for (int i = head[u]; ~i; i = e[i].next) {
    int v = e[i].to;
    dfs(v);
    c[u] += c[v];
  }
}
int find(int u, int x) {
  for (int i = head[u]; ~i; i = e[i].next) {
    int v = e[i].to;
    if (c[v] == x) return find(v, x);
  }
  return u;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  memset(head, -1, sizeof(head));
  cin >> n >> k;
  for (int i = 0; i < k; ++i) {
    cin >> q[i];
    ff[q[i]] = ff[q[i] + n] = true;
  }
  for (int i = 1; i <= n; ++i) cin >> w[i];
  for (int i = 2; i <= n; ++i) {
    int f;
    cin >> f;
    addEdge(f, i);
  }
  for (int i = 1; i <= n; ++i) cin >> w[i + n];
  for (int i = 2; i <= n; ++i) {
    int f;
    cin >> f;
    addEdge(f + n, i + n);
  }
  dfs(1);
  dfs(1 + n);
  int lca1 = find(1, k), m1 = find(lca1, k - 1), s1 = find(lca1, 1);
  int lca2 = find(1 + n, k), m2 = find(lca2, k - 1), s2 = find(lca2, 1);
  int cnt = 0;
  for (int i = 0; i < k; ++i) {
    int w1 = w[lca1], w2 = w[lca2];
    if (m1 != lca1 && (q[i] == s1 || q[i] == lca1)) w1 = w[m1];
    if (m2 != lca2 && (q[i] + n == s2 || q[i] + n == lca2)) w2 = w[m2];
    if (w1 > w2) ++cnt;
  }
  cout << cnt << endl;
  return 0;
}
