#include <bits/stdc++.h>
using ll = long long;
template <class Tp>
using vc = std::vector<Tp>;
template <class Tp>
using vvc = std::vector<std::vector<Tp>>;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
template <typename... Ts>
void dec(Ts &...x) {
  ((--x), ...);
}
template <typename... Ts>
void inc(Ts &...x) {
  ((++x), ...);
}
using namespace std;
void solve(int t_ = 0) {
  auto query = [](string x) {
    cout << "? " << x << endl;
    int n;
    cin >> n;
    vc<int> q(n);
    for (int &i : q) cin >> i;
    for (int &i : q) --i;
    return q;
  };
  auto answer = [](string x) { cout << "! " << x << endl; };
  vvc<int> res{query("abcdefghijklmnopqrstuvwxyz"),
               query("acegikmoqsuwy"),
               query("abefijmnqruvyz"),
               query("abcdijklqrstyz"),
               query("abcdefghqrstuvwx"),
               query("abcdefghijklmnop")};
  vc<int> val(res[0].size());
  for_(i, 0, 5, base) {
    base = 1 << i;
    for (int j : res[i]) val[j] |= base;
  }
  string ans(res[0].size(), ' ');
  string dict =
    "             z y x w v u t s r q p o n m l k j i h g f e d c b a";
  for_(i, 0, res[0].size() - 1) ans[i] = dict[val[i]];
  answer(ans);
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
