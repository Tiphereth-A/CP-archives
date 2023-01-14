#include <cstdio>
#include <iostream>
using namespace std;
template <typename T>
void exgcd(T a, T b, T &gcd, T &x, T &y) {
  if (!b) {
    gcd = a;
    x = 1;
    y = 0;
    return;
  }
  exgcd(b, a % b, gcd, y, x);
  y -= a / b * x;
}
int main() {
  int kase;
  cin >> kase;
  while (kase--) {
    i64 a, b;
    cin >> a >> b;
    i64 g, x, y;
    exgcd(a, b, g, x, y);
    if (g != 1) {
      puts("Not Exist");
      continue;
    }
    ((x %= b) += b) %= b;
    cout << (x == 0 ? b : x) << endl;
  }
}
