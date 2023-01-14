#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  while (cin >> n)
    cout << __builtin_popcount(n) + 30 - __builtin_clz(n) << endl;
  return 0;
}
