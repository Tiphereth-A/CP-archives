#include <cstdio>
#include <iostream>
const int N = 1e5 + 5;
int fa[N << 1];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
int main() {
  int kase;
  scanf("%d", &kase);
  int n, k;
  while (kase--) {
    scanf("%d%d\n", &n, &k);
    for (int i = 1; i <= 2 * n; ++i) fa[i] = i;
    char op;
    for (int x, y, i = 1; i <= k; ++i) {
      scanf("%c%d%d\n", &op, &x, &y);
      if (op == 'A') {
        if (find(x) == find(y + n)) puts("In different gangs.");
        else if (find(x) == find(y)) puts("In the same gang.");
        else puts("Not sure yet.");
      } else {
        fa[find(x)] = find(y + n);
        fa[find(y)] = find(x + n);
      }
    }
  }
}
