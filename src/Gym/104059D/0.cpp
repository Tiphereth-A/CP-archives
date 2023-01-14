#include <bits/stdc++.h>
using ll = long long;
using i64 = ll;
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
  auto query = [](i64 x) {
    cout << "? " << x << endl;
    cin >> x;
    return x;
  };
  auto answer = [](i64 x) { cout << "! " << x << endl; };
  i64 l = 1;
  while (l <= 1e12) {
    i64 res = query(l);
    if (res == l) {
      l = min(i64(1000000000000), l * 2);
      continue;
    }
    answer(l - res);
    break;
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
