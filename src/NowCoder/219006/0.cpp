#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    int a;
    scanf("%d", &a);
    int ans = 1;
    if (a > 1) do {
        ans <<= 1;
      } while (ans < a);
    printf("Input value: %d\n%d\n", a, ans);
    if (i != n) puts("");
  }
  return 0;
}
