#include <bits/stdc++.h>
using namespace std;
struct LinearBasis {
  long long a[63 + 1];
  LinearBasis() { std::fill(a, a + 63 + 1, 0); }
  LinearBasis(long long *x, int n) { build(x, n); }
  void insert(long long t) {
    for (int j = 63; j >= 0; j--) {
      if (!t) return;
      if (!(t & (1ll << j))) continue;
      if (a[j]) t ^= a[j];
      else {
        for (int k = 0; k < j; k++)
          if (t & (1ll << k)) t ^= a[k];
        for (int k = j + 1; k <= 63; k++)
          if (a[k] & (1ll << j)) a[k] ^= t;
        a[j] = t;
        break;
      }
    }
  }
  void build(long long *x, int n) {
    std::fill(a, a + 63 + 1, 0);
    for (int i = 1; i <= n; i++) { insert(x[i]); }
  }
  long long queryMax() {
    long long res = 0;
    for (int i = 0; i <= 63; i++) res ^= a[i];
    return res;
  }
  void mergeFrom(const LinearBasis &other) {
    for (int i = 0; i <= 63; i++) insert(other.a[i]);
  }
  static LinearBasis merge(const LinearBasis &a, const LinearBasis &b) {
    LinearBasis res = a;
    for (int i = 0; i <= 63; i++) res.insert(b.a[i]);
    return res;
  }
};
LinearBasis a;
int main() {
  vector<int> xx;
  uint64_t n;
  cin >> n;
  for (uint64_t i = 0, _; i < n; ++i) {
    cin >> _;
    a.insert(_);
  }
  cout << a.queryMax();
  return 0;
}
