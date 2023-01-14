#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr i64 qpow(i64 a, i64 b, const i64 &mod) {
  i64 res(1);
  a %= mod;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
};
auto solve() -> void {
  i64 n, m, p;
  cin >> n >> m >> p;
  cout << qpow(m, n - 1, p) * qpow(n, m - 1, p) % p << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
