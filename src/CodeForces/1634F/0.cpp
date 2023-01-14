#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const uint32_t OFFSET = 5;
const uint32_t N = 3e5 + OFFSET;
int a[N];
int diff[N], fibo[N];
int cnt_positive;
auto modify = [](unsigned pos, unsigned val, int mod) {
  cnt_positive -= !!diff[pos];
  if ((diff[pos] += val) >= mod) diff[pos] -= mod;
  cnt_positive += !!diff[pos];
};
auto solve() -> void {
  unsigned n, q, mod;
  cin >> n >> q >> mod;
  _for(i, 1, n) cin >> a[i];
  _for(i, 1, n, x) {
    cin >> x;
    if ((a[i] -= x) < 0) a[i] += mod;
  }
  diff[1] = a[1];
  _for(i, 2, n + 2) diff[i] = (a[i] - a[i - 1] + mod * 2 - a[i - 2]) % mod;
  _for(i, 1, n + 2) cnt_positive += !!diff[i];
  fibo[1] = 1;
  _for(i, 2, n + 2) fibo[i] = (fibo[i - 1] + fibo[i - 2]) % mod;
  char op;
  _for(i, 1, q, l, r) {
    cin >> op >> l >> r;
    if (op == 'A') {
      modify(l, 1, mod);
      modify(r + 1, mod - fibo[r - l + 2], mod);
      modify(r + 2, mod - fibo[r - l + 1], mod);
    } else {
      modify(l, mod - 1, mod);
      modify(r + 1, fibo[r - l + 2], mod);
      modify(r + 2, fibo[r - l + 1], mod);
    }
    cout << (cnt_positive ? "NO" : "YES") << '\n';
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
