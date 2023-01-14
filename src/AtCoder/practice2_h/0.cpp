#include <bits/stdc++.h>
using namespace std;
#include <atcoder/twosat.hpp>
using namespace atcoder;
int main() {
  int n, m;
  cin >> n >> m;
  vector<tuple<int, int, bool>> vp;
  for (int i = 0, a, b; i < n; ++i) {
    cin >> a >> b;
    vp.emplace_back(a, i, 0);
    vp.emplace_back(b, i, 1);
  }
  auto vp_ = vp;
  sort(vp.begin(), vp.end());
  two_sat ts(n);
  for (size_t i = 0; i < vp.size(); ++i)
    for (size_t j = i + 1; j < vp.size(); ++j) {
      if (get<0>(vp[j]) - get<0>(vp[i]) >= m) break;
      ts.add_clause(get<1>(vp[i]), get<2>(vp[i]), get<1>(vp[j]), get<2>(vp[j]));
    }
  if (!ts.satisfiable()) {
    cout << "No";
    return 0;
  }
  cout << "Yes\n";
  auto &&__ = ts.answer();
  for (size_t i = 0; i < n; ++i) cout << get<0>(vp_[i * 2 + !__[i]]) << '\n';
  return 0;
}
