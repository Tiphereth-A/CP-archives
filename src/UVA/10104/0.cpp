#include <iostream>
using namespace std;
void exgcd(int a, int b, int &x, int &y) {
  if (!b) {
    x = 1;
    y = 0;
    return;
  }
  exgcd(b, a % b, y, x);
  y -= a / b * x;
}
int main() {
  int a, b, x, y;
  while (cin >> a >> b) {
    x = y = 0;
    exgcd(a, b, x, y);
    cout << x << " " << y << " " << a * x + b * y << endl;
  }
  return 0;
}
