#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  if (!k) {
    printf("-1\n");
    return 0;
  }
  printf("%d ", k);
  for (int i = 2; i <= k; i++) printf("%d%c", i - 1, " \n"[i == n]);
  for (int i = k + 1; i <= n; i++) printf("%d%c", i, " \n"[i == n]);
  return 0;
}
