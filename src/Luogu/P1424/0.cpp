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
  for (unsigned long long i = 0; i < n; ++i) {
    if (x != 7 && x != 6) cnt += 250;
    if (x == 7) x = 1;
    else ++x;
  }
  print(cnt);
  return 0;
}
