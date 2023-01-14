#include <bits/stdc++.h>
using namespace std;
int64_t qpow(int64_t a, int64_t b, const int64_t &mod) {
  int64_t res(1);
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
};
int main() {
  int t_;
  cin >> t_;
  for (int64_t n, p; t_; t_--) {
    cin >> n >> p;
    if (p <= n) {
      cout << "0\n";
      continue;
    }
    int64_t a = 1;
    for (int64_t i = n + 1; i < p; i++) a = a * i % p;
    cout << (p - 1) * qpow(a, p - 2, p) % p << '\n';
  }
  return 0;
}
