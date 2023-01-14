#include <bits/stdc++.h>
using namespace std;
int main() {
  int a[5], min = 10000;
  for (int i = 0; i < 5; i++) cin >> a[i];
  a[2] /= 2;
  a[3] /= 7;
  a[4] /= 4;
  for (int i = 0; i < 5; i++) min = (min > a[i]) ? a[i] : min;
  cout << min;
  return 0;
}
