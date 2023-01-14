#include <bits/stdc++.h>
using namespace std;
int main() {
  int kase;
  cin >> kase;
  while (kase--) {
    int n;
    cin >> n;
    cout << (n - (n & 1)) / 2 + 1 << endl;
  }
  return 0;
}
