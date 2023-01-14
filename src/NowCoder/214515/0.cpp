#include <iostream>
using namespace std;
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
char m[4][4];
int main() {
  cin >> m[0] >> m[1] >> m[2];
  int a = 0, b = 0;
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j) b += (m[i][j] == '.');
  b = b * (b - 1) * (b - 2) / 6;
  for (int i = 0; i < 3; ++i) {
    bool f = 1;
    for (int j = 0; j < 3; ++j)
      if (m[i][j] != '.') f = 0;
    a += f;
  }
  for (int i = 0; i < 3; ++i) {
    bool f = 1;
    for (int j = 0; j < 3; ++j)
      if (m[j][i] != '.') f = 0;
    a += f;
  }
  bool f = 1;
  for (int j = 0; j < 3; ++j)
    if (m[j][j] != '.') f = 0;
  a += f;
  f = 1;
  for (int j = 0; j < 3; ++j)
    if (m[2 - j][j] != '.') f = 0;
  a += f;
  if (a == 0) {
    cout << 0;
    return 0;
  }
  int g = gcd(a, b);
  a /= g;
  b /= g;
  cout << a << ' ' << b;
}
