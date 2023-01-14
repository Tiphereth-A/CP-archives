#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
using namespace std;
using i64 = long long;
const i64 MOD = 1e9 + 9;
const i64 N = 1e5 + 5;
i64 qpow(i64 a, i64 b = MOD - 2, const i64 &MOD = MOD) {
  i64 res(1);
  for (; b; b >>= 1, (a *= a) %= MOD)
    if (b & 1) (res *= a) %= MOD;
  return res;
};
const i64 X1 = 691504013, X2 = 308495997;
i64 a[N], b[N], fact[N], ifact[N];
i64 comb(i64 n, i64 k) {
  return (fact[n] * ifact[n - k]) % MOD * ifact[k] % MOD;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  fact[0] = ifact[0] = 1;
  for (int i = 1; i < N; ++i) fact[i] = fact[i - 1] * i % MOD;
  ifact[N - 1] = qpow(fact[N - 1]);
  for (int i = N - 2; i; --i) ifact[i] = ifact[i + 1] * (i + 1) % MOD;
  a[0] = b[0] = 1;
  for (int i = 1; i < N; ++i) a[i] = a[i - 1] * X1 % MOD;
  for (int i = 1; i < N; ++i) b[i] = b[i - 1] * X2 % MOD;
  int t_;
  cin >> t_;
  while (t_--) {
    i64 n, k;
    cin >> n >> k;
    i64 ans = 0;
    for (i64 r = 0, sgn = 1, t; r <= k; ++r, sgn = -sgn) {
      if ((t = a[k - r] * b[r] % MOD) == 1) {
        (ans += MOD + sgn * n % MOD * comb(k, r) % MOD) %= MOD;
        continue;
      }
      (ans += MOD + sgn * comb(k, r) * t % MOD * (qpow(t, n) - 1) % MOD *
                      qpow(t - 1) % MOD) %= MOD;
    }
    cout << ans * qpow(ISQRT5, k) % MOD << '\n';
  }
}
