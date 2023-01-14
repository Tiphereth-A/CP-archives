#include <bits/stdc++.h>
using ll = long long;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
template <class Tp>
Tp dec(Tp &i) {
  return --i;
}
template <class Tp>
Tp inc(Tp &i) {
  return ++i;
}
using namespace std;
void solve(int t_ = 0) {
  int n;
  cin >> n;
  set<string> g0;
  for_(i, 1, n, m) {
    cin >> m;
    vector<string> picked;
    string s;
    for_(i, 1, m) {
      cin >> s;
      if (s.find("bie") != string::npos && !g0.count(s)) {
        g0.insert(s);
        picked.push_back(s);
      }
    }
    if (picked.empty()) {
      cout << "Time to play Genshin Impact, Teacher Rice!\n";
      continue;
    }
    for (auto &&i : picked) cout << i << '\n';
  }
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
