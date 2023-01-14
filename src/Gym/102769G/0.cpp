#include <bits/stdc++.h>
using namespace std;
void print(int kase, int res) {
  cout << "Case #" << kase << ": " << res << endl;
}
int qpow(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a *= a)
    if (b & 1) res *= a;
  return res;
}
int main() {
  int _kase;
  cin >> _kase;
  for (int kase = 1; kase <= _kase; ++kase) {
    int n, k;
    cin >> n >> k;
    int limit_i = floor(pow(n, 1.0 / k));
    if (k == 1 || limit_i == 1) {
      print(kase, n);
      continue;
    }
    int cnt = 0;
    for (int i = 1; i <= limit_i; ++i) {
      int tmp = ceil(1.0 * (min(qpow(i + 1, k), n) - qpow(i, k)) / i);
      cnt += tmp;
    }
    print(kase, cnt);
  }
  return 0;
}
