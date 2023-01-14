#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
const int OFFSET = 5;
const int N = 1e4 + OFFSET;
const u64 p = 1e4;
u64 s[N];
u64 qpow(u64 a, u64 b, const u64 &mod = p) {
  u64 res(1);
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int kase;
  cin >> kase;
  while (kase--) {
    u64 n, k;
    cin >> n >> k;
    _for(i, 1, p) s[i] = (s[i - 1] + qpow(i, k)) % p;
    cout << (n / p % p * s[p] + s[n % p]) % p << '\n';
  }
  return 0;
}
