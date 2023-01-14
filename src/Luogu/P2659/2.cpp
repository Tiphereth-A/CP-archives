#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
bool operator<(const pii &lhs, const pii &rhs) { return lhs.first < rhs.first; }
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n;
  cin >> n;
  vector<pii> v;
  _for(i, 1, n, _) {
    cin >> _;
    v.emplace_back(_, i);
  }
  i64 ans = 0;
  vector<pii> s;
  s.emplace_back(0, 0);
  for (const auto &i : v) {
    if (s.size() == 1) {
      s.push_back(i);
      continue;
    }
    while (i < s.back()) {
      chkmax(ans,
             1ll * s.back().first * (i.second - (s.end() - 2)->second - 1));
      s.pop_back();
    }
    s.push_back(i);
  }
  for (auto it = s.begin() + 1; it != s.end(); ++it)
    chkmax(ans, 1ll * it->first * (n - (it - 1)->second));
  cout << ans;
  return 0;
}
