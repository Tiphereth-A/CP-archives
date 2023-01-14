#include <bits/stdc++.h>
using ull = unsigned long long;
using u64 = ull;
template <class Tp>
using vc = std::vector<Tp>;
template <class Tp>
Tp dec(Tp &i) {
  return --i;
}
template <class Tp>
Tp inc(Tp &i) {
  return ++i;
}
using namespace std;
const string RES[2] = {"BAD", "GOOD"};
void solve(int t_ = 0) {
  u64 n, p;
  cin >> n >> p;
  vc<u64> a(n);
  for (auto &i : a) cin >> i;
  auto f = [&p](auto &&f, u64 x) -> u64 {
    if ((p & 1) || (x < p)) return x & 1;
    if (x == p) return 2;
    return f(f, x % (p + 1));
  };
  u64 x = 0;
  for (auto &i : a) x ^= f(f, i);
  cout << RES[!!x] << '\n';
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
