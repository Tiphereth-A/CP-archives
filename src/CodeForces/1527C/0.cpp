#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
#define _all(a) (a).begin(), (a).end()
#define _set_nul_n(a, n) memset(a, 0, sizeof(a[0]) * (n))
const int OFFSET = 5;
const int N = 1e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
i64 sum[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int kase;
  cin >> kase;
  while (kase--) {
    int n, _;
    vi a;
    cin >> n;
    _for(i, 1, n) {
      cin >> _;
      a.push_back(_);
    }
    vi b = a;
    sort(_all(a));
    a.erase(unique(_all(a)), a.end());
    for (int &i : b) i = lower_bound(_all(a), i) - a.begin() + 1;
    i64 ans = 0;
    _for(i, 1, n) {
      ans += sum[b[i - 1]] * (n - i + 1);
      sum[b[i - 1]] += i;
    }
    cout << ans << '\n';
    _set_nul_n(sum, n + 1);
  }
  return 0;
}
