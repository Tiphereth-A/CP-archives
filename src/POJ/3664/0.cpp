#include <algorithm>
#include <cstdio>
struct node {
  int f, s, id;
} c[50005];
bool cmp1(const node &lhs, const node &rhs) { return lhs.f > rhs.f; }
bool cmp2(const node &lhs, const node &rhs) { return lhs.s > rhs.s; }
int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &c[i].f, &c[i].s);
    c[i].id = i;
  }
  std::sort(c + 1, c + n + 1, cmp1);
  std::sort(c + 1, c + k + 1, cmp2);
  printf("%d\n", c[1].id);
  return 0;
}
