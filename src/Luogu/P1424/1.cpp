#include <bits/stdc++.h>
using namespace std;
void print(__uint128_t x) {
  if (x > 9) print(x / 10);
  putchar(x % 10 + '0');
}
int main() {
  int x, n;
  __uint128_t cnt = 0;
  cin >> x >> n;
  for (unsigned long long i = x; i < x + n; ++i) {
    if (i % 7 == 0 || i % 7 == 6) continue;
    cnt += 250;
  }
  print(cnt);
  return 0;
}
