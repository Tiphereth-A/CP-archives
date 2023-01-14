#include <bits/stdc++.h>
using namespace std;
int a[1005];
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  sort(a + 1, a + n + 1);
  int s = INT_MAX;
  for (int j = a[1], sum; j <= a[n]; j++) {
    sum = 0;
    for (int i = 1; i <= n; i++) {
      if (a[i] - j > 17) sum += (a[i] - j - 17) * (a[i] - j - 17);
      if (a[i] < j) sum += (a[i] - j) * (a[i] - j);
    }
    s = min(sum, s);
  }
  cout << s;
}
