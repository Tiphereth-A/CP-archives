#include <bits/stdc++.h>
using namespace std;
void solve() {
  int n;
  cin >> n;
  vector<int> deg(n);
  for (int i = 1, u, v; i < n; ++i) {
    cin >> u >> v;
    ++deg[u - 1];
    ++deg[v - 1];
  }
  cout << (ranges::any_of(deg, [](int x) -> bool { return ~x & 1; }) ? "Hifuu" :
                                                                       "Luna")
       << '\n';
}
int main() {
  cin.tie(nullptr)->ios::sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) solve();
  return 0;
}
