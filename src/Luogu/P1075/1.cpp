#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin >> n;
  int s = ceil(sqrt(n));
  int a, b;
  for (int i = 2; i <= s; i++) {
    if (n % i == 0) {
      a = i;
      b = n / i;
      break;
    }
  }
  cout << ((a > b) ? a : b);
  return 0;
}
