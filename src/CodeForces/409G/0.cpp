#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); i++)
using namespace std;
double x, y, sum;
int main() {
  ios::sync_with_stdio(false);
  int n;
  cin >> n;
  _for(i, 1, n) {
    cin >> x >> y;
    sum += y;
  }
  sum /= n;
  sum += 5;
  printf("%.3lf", sum);
  return 0;
}
