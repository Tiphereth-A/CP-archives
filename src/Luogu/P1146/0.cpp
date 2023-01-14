#include <bits/stdc++.h>
using namespace std;
bool c[105];
int main() {
  int n;
  cin >> n;
  cout << n << endl;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (j != i) c[j] = !c[j];
      cout << c[j];
    }
    cout << endl;
  }
  return 0;
}
