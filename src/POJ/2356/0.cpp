#include <cstdio>
const int N = 1e4 + 5;
int a[N], sum[N];
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    if (!(sum[i] = (sum[i - 1] + a[i]) % n)) {
      printf("%d\n", i);
      for (int j = 1; j <= i; ++j) printf("%d\n", a[j]);
      return 0;
    }
  }
  for (int i = 1; i < n; ++i)
    for (int j = i + 1; j <= n; ++j)
      if (sum[i] == sum[j]) {
        printf("%d\n", j - i);
        for (int k = i + 1; k <= j; ++k) printf("%d\n", a[k]);
        return 0;
      }
}
