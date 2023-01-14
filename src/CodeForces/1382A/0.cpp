#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
const int N = 1e4 + 5;
int a[N], b[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int kase;
  cin >> kase;
  while (kase--) {
    int n, m, _;
    cin >> n >> m;
    _for(i, 1, n) cin >> a[i];
    _for(i, 1, m) cin >> b[i];
    _for(i, 1, n)
      _for(j, 1, m)
        if (a[i] == b[j]) {
          cout << "YES\n1 " << a[i] << '\n';
          goto __end_kase;
        }
    cout << "NO\n";
  __end_kase:;
  }
  return 0;
}
