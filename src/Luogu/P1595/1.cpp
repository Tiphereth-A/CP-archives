#include <bits/stdc++.h>
using namespace std;
unsigned long long a[25] = {0, 0, 1, 2};
int main() {
  for (int i = 4; i <= 20; ++i) a[i] = (i - 1) * (a[i - 1] + a[i - 2]);
  int n;
  cin >> n;
  cout << a[n];
  return 0;
}
