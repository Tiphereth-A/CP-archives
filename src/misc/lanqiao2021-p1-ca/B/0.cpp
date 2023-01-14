#include <iostream>
using namespace std;
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
const int X = 20, Y = 21;
int main() {
  int ans = X + Y;
  for (int x = 1; x < X; ++x)
    for (int y = 1; y < Y; ++y)
      if (gcd(x, y) == 1)
        ans += 2 * ((X - x) * (Y - y) -
                    (X >= 2 * x && Y >= 2 * y) * (X - 2 * x) * (Y - 2 * y));
  cout << ans;
  return 0;
}
