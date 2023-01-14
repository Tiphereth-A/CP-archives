#include <bits/stdc++.h>
using namespace std;
int main() {
  int a[1010] = {0}, n;
  cin >> n;
  int m;
  for (int i = 1; i <= n; i++) {
    cin >> m;
    a[m] = 1;
  }
  m = 0;
  for (int i = 1; i <= 1000; i++)
    if (a[i]) m++;
  cout << m << endl;
  for (int i = 1; i <= 1000; i++)
    if (a[i]) cout << i << ' ';
  return 0;
}
