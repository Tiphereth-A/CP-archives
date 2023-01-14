#include <bits/stdc++.h>
using namespace std;
int main() {
  int l, m, s, e, ans = 0, j;
  cin >> l >> m;
  int t[10010];
  memset(t, 0, sizeof(t));
  for (int i = 1; i <= m; i++) {
    cin >> s >> e;
    for (j = s; j <= e; j++) { t[j]++; };
  };
  for (int i = 0; i <= l; i++) {
    if (t[i] == 0) ans++;
  }
  cout << ans;
  return 0;
}
