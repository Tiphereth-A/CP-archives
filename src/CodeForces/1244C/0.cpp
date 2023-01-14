#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
long long n, p, w, d;
int main() {
  cin >> n >> p >> w >> d;
  long long x, y = 0;
  while (y < w && (p - y * d) % w) ++y;
  if (y == w) {
    cout << -1;
    return 0;
  }
  x = (p - y * d) / w;
  if (x + y > n || x < 0) cout << -1;
  else cout << x << " " << y << " " << n - x - y;
  return 0;
}
