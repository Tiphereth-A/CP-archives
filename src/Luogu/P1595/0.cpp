#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
unsigned long long a[25] = {0, 0, 1, 2};
int main() {
  for (unsigned long long i = 4; i <= 20; ++i)
    a[i] = (i - 1) * (a[i - 1] + a[i - 2]);
  int n;
  cin >> n;
  cout << a[n];
  return 0;
}
