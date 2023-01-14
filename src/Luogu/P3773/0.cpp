#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n;
  cin >> n;
  vector<int> a(n);
  for (auto &i : a) cin >> i;
  vector<int> f(*max_element(a.begin(), a.end()) + 1);
  int ans = 0;
  for (auto i : a) {
    for (int S = i - 1 & i; S; S = S - 1 & i) (f[S] += f[i] + 1) %= MOD;
    (ans += f[i]) %= MOD;
  }
  cout << ans << '\n';
  return 0;
}
