#include <bits/stdc++.h>
using namespace std;
int main() {
  double a, b, c, d;
  cin >> a >> b >> c >> d;
  printf("%.8lf", a + (c - a) * b / (b + d));
  return 0;
}
