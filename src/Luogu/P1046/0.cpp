#include <bits/stdc++.h>
using namespace std;
int main() {
  int h[10], t, ans = 0;
  for (int i = 0; i < 10; i++) { cin >> h[i]; };
  cin >> t;
  t += 30;
  for (int i = 0; i < 10; i++) {
    if (h[i] <= t) ans++;
  };
  cout << ans;
  return 0;
}
