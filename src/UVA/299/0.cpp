#include <bits/stdc++.h>
using std::swap;
int num[55];
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &num[i]);
    int cnt = 0;
    for (int i = 0; i < n - 1; ++i)
      for (int j = 1; j < n - i; ++j)
        if (num[j - 1] > num[j]) {
          ++cnt;
          swap(num[j - 1], num[j]);
        }
    printf("Optimal train swapping takes %d swaps.\n", cnt);
  }
  return 0;
}
