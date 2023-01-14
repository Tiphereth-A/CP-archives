#include <bits/stdc++.h>
using namespace std;
int main() {
  double a, b;
  cin >> a;
  if (a > 400) {
    a -= 400;
    b = 183.52 + a * 0.5663;
  } else if (a > 150) {
    a -= 150;
    b = 66.945 + a * 0.4663;
  } else {
    b = a * 0.4463;
  };
  printf("%.1lf", b);
  return 0;
}
