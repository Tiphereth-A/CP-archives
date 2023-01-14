#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
template <typename A>
A Max(const A &x, const A &y) {
  return x > y ? x : y;
}
template <typename A>
A Min(const A &x, const A &y) {
  return x < y ? x : y;
}
const int N = 2e4 + 5;
struct node {
  i64 a, b, index;
  bool operator<(node n) const {
    return (index == n.index) ? ((index > 0) ? (b > n.b) : (a < n.a)) :
                                (index < n.index);
  }
} minister[N];
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d", &n);
    _for(i, 1, n) {
      scanf("%lld%lld", &minister[i].a, &minister[i].b);
      minister[i].index = (minister[i].a > minister[i].b) ?
                            1 :
                            ((minister[i].a < minister[i].b) ? -1 : 0);
    }
    std::sort(minister + 1, minister + n + 1);
    i64 ans = minister[1].a + minister[1].b, sum = minister[1].a;
    _for(i, 2, n) ans = Max(ans, (sum += minister[i].a)) + minister[i].b;
    printf("%lld\n", ans);
  }
  return 0;
}
