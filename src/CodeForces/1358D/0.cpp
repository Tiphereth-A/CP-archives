#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (auto i = (l); i <= (r); ++i)
#define _repr(i, r, l) for (auto i = (r); i > (l); --i)
typedef long long i64;
const int N = 4e5 + 5;
i64 d[N], sum[N];
int main() {
#define _S(n) ((n) * ((n) + 1) / 2)
  ios::sync_with_stdio(false);
  cin.tie(0);
  i64 n, x;
  cin >> n >> x;
  _for(i, 1, n) {
    cin >> d[i];
    sum[i] = sum[i - 1] + d[i];
  }
  _for(i, n + 1, 2 * n) sum[i] = sum[i - 1] + (d[i] = d[i - n]);
  i64 ans = 0, _ = 0, l = n *= 2, diff = 0;
  _repr(r, n, n / 2) {
    while (sum[r] - sum[l - 1] <= x) {
      _ += _S(d[l]);
      --l;
    }
    diff = sum[r] - sum[l - 1] - x;
    _ += _S(d[l]) - _S(diff);
    if (_ > ans) ans = _;
    _ -= _S(d[r]) + _S(d[l]) - _S(diff);
  }
  cout << ans;
  return 0;
}
