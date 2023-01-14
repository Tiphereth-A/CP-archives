#include <bits/stdc++.h>
using namespace std;
int a[100005];
int main() {
  int n, s;
  int min_a = INT_MAX, ans = 0;
  scanf("%d%d", &n, &s);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
    min_a = min(min_a, a[i] + n * s);
  }
  for (int i = n; i; --i) {
    ans = max(ans, min_a - i * s);
    min_a = min(min_a, a[i]);
  }
  printf("%d", ans);
}
