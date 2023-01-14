#include <bits/stdc++.h>
using namespace std;
const int N = 1 << 21;
int cnt[N] = {1};
int main() {
  int n;
  cin >> n;
  int state = 0;
  long long ans = 0;
  for (int i = 1, _; i <= n; ++i) {
    cin >> _;
    ans += cnt[state ^= (1 << _)]++;
  }
  cout << ans;
  return 0;
}
