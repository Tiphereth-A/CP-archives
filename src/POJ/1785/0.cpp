#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 5e4 + 5;
struct Node {
  char name[15];
  int w;
  bool operator<(const Node &other) const {
    return strcmp(name, other.name) < 0;
  }
} tree[N];
struct ST {
  int w, idx;
} st[N][20];
int logn[N];
int query(int l, int r) {
  int k = logn[r - l + 1];
  return st[l][k].w > st[r - (1 << k) + 1][k].w ? st[l][k].idx :
                                                  st[r - (1 << k) + 1][k].idx;
}
void solve(int l, int r) {
  if (l > r) return;
  int max_idx = query(l, r);
  putchar('(');
  solve(l, max_idx - 1);
  printf("%s/%d", tree[max_idx].name, tree[max_idx].w);
  solve(max_idx + 1, r);
  putchar(')');
}
char _[105];
int main() {
  for (int i = 2; i < N; ++i) logn[i] = logn[i / 2] + 1;
  int n;
  while (~scanf("%d ", &n) && n) {
    memset(st, 0, sizeof(st));
    for (int i = 1; i <= n; ++i) {
      scanf("%s", _);
      sscanf(_, "%[^/]/%d", tree[i].name, &tree[i].w);
    }
    std::sort(tree + 1, tree + n + 1);
    for (int i = 1; i <= n; ++i) st[i][0] = {tree[i].w, i};
    for (int i = 1; i <= logn[n]; ++i)
      for (int j = 1; j + (1 << i) - 1 <= n; ++j)
        st[j][i] = st[j][i - 1].w > st[j + (1 << i - 1)][i - 1].w ?
                     st[j][i - 1] :
                     st[j + (1 << i - 1)][i - 1];
    solve(1, n);
    puts("");
  }
}
