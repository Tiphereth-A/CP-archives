#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t_ = 0;
  cin >> t_;
  while (t_--) {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int &i : a) cin >> i;
    sort(a.begin(), a.end());
    int ans = 0, lst = INT_MIN;
    for (int i : a) {
      int l = i - k, r = i + k;
      if (lst >= r) continue;
      lst = max(lst + 1, l);
      ++ans;
    }
    cout << ans << '\n';
  }
  return 0;
}
