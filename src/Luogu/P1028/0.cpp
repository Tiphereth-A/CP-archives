#include <bits/stdc++.h>
using namespace std;
int main() {
  long a[1010];
  int n;
  cin >> n;
  a[1] = 1;
  for (int i = 1; i <= n; i++) {
    a[i] = 1;
    int f = floor(i / 2);
    for (int j = 1; j <= f; j++) a[i] += a[j];
  }
  cout << a[n];
  return 0;
}
