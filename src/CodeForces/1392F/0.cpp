#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  scanf("%d", &n);
  long long sum = 0, _;
  for (int i = 1; i <= n; ++i) {
    scanf("%lld", &_);
    sum += _;
  }
  _ = sum - n * (n + 1ll) / 2;
  for (int i = 1; i <= n; ++i)
    printf("%lld%c", i + _ / n + (i <= _ % n), " \n"[i == n]);
  return 0;
}
