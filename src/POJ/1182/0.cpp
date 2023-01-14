#include <cstdio>
const int N = 1e5 + 5;
int n, k;
int fa[N * 3];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
bool judge_a(int x, int y) {
  return find(x) == find(y + n) || find(x + n) == find(y);
}
bool judge_e(int x, int y) {
  return find(x) == find(y) || find(x) == find(y + n);
}
void merge_a(int x, int y) {
  fa[find(x)] = find(y);
  fa[find(x + n)] = find(y + n);
  fa[find(x + n * 2)] = find(y + n * 2);
}
void merge_e(int x, int y) {
  fa[find(x)] = find(y + n * 2);
  fa[find(x + n)] = find(y);
  fa[find(x + n * 2)] = find(y + n);
}
int main() {
  scanf("%d%d", &n, &k);
  int ans = 0;
  for (int i = 1; i <= 3 * n; ++i) fa[i] = i;
  for (int op, x, y, i = 1; i <= k; ++i) {
    scanf("%d%d%d", &op, &x, &y);
    if ((x > n || y > n) || (op == 2 && x == y)) {
      ++ans;
      continue;
    }
    if (op == 1) {
      if (judge_a(x, y)) ++ans;
      else merge_a(x, y);
    } else {
      if (judge_e(x, y)) ++ans;
      else merge_e(x, y);
    }
  }
  printf("%d", ans);
  return 0;
}
