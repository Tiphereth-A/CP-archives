#include <bits/stdc++.h>
using namespace std;
int main() {
  int x;
  unsigned long long n, m = 0;
  cin >> x >> n;
  for (int i = 0; i < n; ++i) {
    if (x < 6) m += 250;
    if (x == 7) x = 1;
    else x++;
  };
  cout << m;
  return 0;
}
