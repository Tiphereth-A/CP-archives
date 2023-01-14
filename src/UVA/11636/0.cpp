#include <cmath>
#include <cstdio>
long long x;
int main() {
  for (long long m = 1; m; ++m) {
    scanf("%lld", &x);
    if (x < 0) break;
    printf("Case %lld: %lld\n", m, (long long)ceil(std::log2(x)));
  }
  return 0;
}
