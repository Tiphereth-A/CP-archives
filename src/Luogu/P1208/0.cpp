#include <bits/stdc++.h>
#define N 5005
struct node {
  int v, num;
} f[N];
int n, m, ans, sum;
bool cmp(node a, node b) { return a.v < b.v; }
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; ++i) scanf("%d%d", &f[i].v, &f[i].num);
  std::sort(f + 1, f + m + 1, cmp);
  for (int i = 1; i <= m; ++i) {
    sum += f[i].num;
    ans += f[i].v * f[i].num;
    if (n <= sum + f[i + 1].num) {
      ans += (n - sum) * f[i + 1].v;
      break;
    }
  }
  printf("%d", ans);
  return 0;
}
