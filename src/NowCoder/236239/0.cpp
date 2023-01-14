#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _rfor(i, r, l, vals...)                                      \
  for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vals; \
       i >= i##end;                                                  \
       --i)
const int N = 2e5 + 5;
int a[N];
auto solve() -> void {
  int n;
  cin >> n;
  _for(i, 1, n) cin >> a[i];
  int maxl = 0, nowl = 0;
  _for(i, 1, n) {
    if (a[i] < a[i - 1]) ++nowl;
    else {
      maxl = max(maxl, nowl);
      nowl = 0;
    }
  }
  maxl = max(maxl, nowl);
  nowl = 0;
  _rfor(i, n, 1) {
    if (a[i] < a[i + 1]) ++nowl;
    else {
      maxl = max(maxl, nowl);
      nowl = 0;
    }
  }
  cout << max(maxl, nowl);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
