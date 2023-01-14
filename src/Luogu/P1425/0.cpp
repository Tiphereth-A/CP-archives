#include <bits/stdc++.h>
using namespace std;
int main() {
  int a, b, c, d;
  cin >> a >> b >> c >> d;
  c -= a;
  d -= b;
  if (d < 0) {
    c--;
    d += 60;
  };
  cout << c << " " << d;
  return 0;
}
