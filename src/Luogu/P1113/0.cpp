#include <bits/stdc++.h>
using namespace std;
int n, l, t, a[10005], ans;
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &i);
    scanf("%d", &l);
    int _ = 0;
    while (scanf("%d", &t) && t) _ = max(a[t], _);
    a[i] = _ + l;
    ans = max(a[i], ans);
  }
  printf("%d\n", ans);
  return 0;
}
