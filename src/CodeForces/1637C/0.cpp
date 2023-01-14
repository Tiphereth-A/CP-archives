#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _run_return(expressions) \
  {                              \
    expressions;                 \
    return;                      \
  }
const uint32_t OFFSET = 5;
const uint32_t N = 1e5 + OFFSET;
int64_t a[N];
void solve() {
  int n;
  cin >> n;
  _for(i, 1, n) cin >> a[i];
  if (n == 3 && (a[2] & 1)) _run_return(cout << "-1\n");
  if (!count_if(a + 2, a + n, [](auto i) -> bool { return i > 1; }))
    _run_return(cout << "-1\n");
  cout << (count_if(a + 2, a + n, [](auto i) -> bool { return i & 1; }) +
           accumulate(a + 2, a + n, 1ll)) /
            2
       << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int _t;
  cin >> _t;
  while (_t--) solve();
  return 0;
}
