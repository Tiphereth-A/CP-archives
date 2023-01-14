#include <bits/stdc++.h>
using namespace std;
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
#define foreach_cref_(i, container) for (const auto &i : (container))
#define all_(a) (a).begin(), (a).end()
auto solve([[maybe_unused]] int t_) -> void {
  int n;
  cin >> n;
  string s;
  string ret;
  vector<string> vs;
  vs.reserve(n);
  for_(i, 0, n - 1) {
    cin >> s;
    vs.push_back(s);
  }
  sort(all_(vs), [](auto &&s1, auto &&s2) { return s1 + s2 < s2 + s1; });
  foreach_cref_(i, vs) ret += i;
  cout << ret;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve(0);
  return 0;
}
