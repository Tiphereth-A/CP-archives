#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
#define N 100005
using namespace std;
ll t, a[N], b[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  cin >> t;
  while (t--) {
    ll m, n;
    cin >> n >> m;
    ll f = 0;
    _for(i, 1, n) {
      cin >> a[i];
      if (a[i] == 1) {
        --i;
        --n;
      }
    }
    _for(i, 1, m) {
      cin >> b[i];
      if (b[i] == 1) {
        --i;
        --m;
      }
    }
    if (f == 1 || n - m != 1 || n == 0) {
      cout << "NO\n";
      continue;
    }
    sort(a + 1, a + n + 1, greater<ll>());
    sort(b + 1, b + m + 1, greater<ll>());
    ll p = 0;
    _for(i, 1, m)
      if (a[i] != b[i]) {
        p = a[i];
        break;
      }
    if (!p) p = a[n];
    ll sq = sqrt(p);
    _for(i, 2, sq)
      if (p % i == 0) {
        f = -1;
        break;
      }
    cout << ((f == -1) ? "NO" : "YES") << endl;
  }
  return 0;
}
