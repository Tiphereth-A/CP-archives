#include <bits/stdc++.h>
using namespace std;
using pii = pair<i64, i64>;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
#define _all(a) (a).begin(), (a).end()
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n;
  cin >> n;
  vector<pii> v;
  _for(i, 1ll, n, l, r) {
    cin >> l >> r;
    v.emplace_back(l, 1);
    v.emplace_back(r + 1, -1);
  }
  sort(_all(v));
  vector<i64> ans(n + 1);
  int _ = 0;
  for (auto i = v.begin(); i != v.end() - 1; ++i)
    ans[_ += i->second] += (i + 1)->first - i->first;
  _for(i, 1, n) cout << ans[i] << " \n"[i == n];
  return 0;
}
