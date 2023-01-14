#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (auto i = (l); i <= (r); ++i)
#define _fd(i, r, l) for (auto i = (r); i >= (l); --i)
const int N = 1e5 + 5;
int s[N], f[N];
int main() {
  int kase;
  cin >> kase;
  while (kase--) {
    int n, ans = 1;
    cin >> n;
    _for(i, 1, n) f[i] = 1;
    _for(i, 1, n) cin >> s[i];
    _fd(i, n / 2, 1) for (int j = i; j <= n; j += i) if (s[j] > s[i]) ans =
      max(ans, f[i] = max(f[i], f[j] + 1));
    cout << ans << endl;
  }
  return 0;
}
