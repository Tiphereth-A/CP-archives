#include <bits/stdc++.h>
using namespace std;
const int OFFSET = 5, N = 2e5 + OFFSET;
unordered_map<int, int> m[N];
int fa[N], sz[N];
int find(int x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
void merge(int x, int y) {
  x = find(x);
  y = find(y);
  if (x == y) return;
  if (sz[x] > sz[y]) swap(x, y);
  for (const auto &i : m[x]) m[y][i.first] += m[x][i.first];
  sz[y] += sz[x];
  fa[x] = y;
}
int a[N];
int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  for (int i = i; i <= n; ++i) {
    fa[i] = i;
    sz[i] = 1;
  }
  for (int i = 1; i <= n; ++i) scanf("%d", a + i);
  for (int i = 1; i <= n; ++i) ++m[i][a[i]];
  for (int i = 1, x, y, op; i <= q; ++i) {
    scanf("%d%d%d", &op, &x, &y);
    if (op == 1) merge(x, y);
    else printf("%d\n", m[find(x)][y]);
  }
  return 0;
}
