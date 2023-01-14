#include <bits/stdc++.h>
using namespace std;
int main() {
  int a, b, d = 0, max = 0;
  for (int i = 1; i <= 7; i++) {
    cin >> a >> b;
    int c = a + b;
    if ((c >= 8) && (c > max)) {
      d = i;
      max = c;
    };
  };
  cout << d;
  return 0;
}
