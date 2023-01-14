#include <bits/stdc++.h>
using namespace std;
const int OFFSET = 5, N = 2e5 + OFFSET;
int a[N];
int main() {
  int n;
  cin >> n;
  int max1 = -1, max2 = -2;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    if (a[i] >= max1) {
      max2 = max1;
      max1 = a[i];
    } else if (a[i] > max2) max2 = a[i];
  }
  for (int i = 1; i <= n; ++i)
    cout << (a[i] == max1 ? max2 : max1) << " \n"[i == n];
  return 0;
}
