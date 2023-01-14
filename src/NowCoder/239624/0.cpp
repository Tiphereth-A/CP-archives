#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using i128 = __int128_t;
int cnt[16];
ostream &operator<<(ostream &os, i128 n) {
  if (n > 9) os << (i128)(n / 10);
  os << (uint32_t)(n % 10);
  return os;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  i64 n;
  cin >> n;
  vector<i64> v;
  v.reserve(n);
  for (int i = 0, x; i < n; ++i) {
    cin >> x;
    v.push_back(x);
  }
  for (auto &&x : v)
    for (int j = 0; j < 16; ++j)
      if (x & (1 << j)) ++cnt[j];
  for (int i = 0; i < n; ++i) {
    auto &now = v[i];
    now = 0;
    for (int j = 0; j < 16; ++j)
      if (cnt[j] > i) now |= (1 << j);
  }
  i128 sum = accumulate(v.begin(), v.end(), i128{0});
  i128 _1 = 0, _2 = i128{n} * n * n;
  for (auto &&i : v) _1 += i128{i * n - sum} * i128{i * n - sum};
  auto &&g = __gcd(_1, _2);
  _1 /= g;
  _2 /= g;
  cout << _1 << '/' << _2;
  return 0;
}
