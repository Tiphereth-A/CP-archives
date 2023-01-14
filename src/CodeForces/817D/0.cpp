#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _rfor(i, r, l, vals...)                                      \
  for (make_signed_t<decltype(r - l)> i = (r), i##end = (l), ##vals; \
       i >= i##end;                                                  \
       --i)
const uint32_t OFFSET = 5;
const uint32_t N = 1e6 + OFFSET;
int a[N];
int lge[N], lle[N], rge[N], rle[N];
void solve() {
  int n;
  cin >> n;
  _for(i, 1, n) cin >> a[i];
  {
    stack<int> monos;
    _for(i, 1, n) {
      while (!monos.empty() && a[monos.top()] < a[i]) monos.pop();
      lge[i] = monos.empty() ? 0 : monos.top();
      monos.push(i);
    }
  }
  {
    stack<int> monos;
    _for(i, 1, n) {
      while (!monos.empty() && a[monos.top()] > a[i]) monos.pop();
      lle[i] = monos.empty() ? 0 : monos.top();
      monos.push(i);
    }
  }
  {
    stack<int> monos;
    _rfor(i, n, 1) {
      while (!monos.empty() && a[monos.top()] <= a[i]) monos.pop();
      rge[i] = monos.empty() ? n + 1 : monos.top();
      monos.push(i);
    }
  }
  {
    stack<int> monos;
    _rfor(i, n, 1) {
      while (!monos.empty() && a[monos.top()] >= a[i]) monos.pop();
      rle[i] = monos.empty() ? n + 1 : monos.top();
      monos.push(i);
    }
  }
  i64 ans = 0;
  _for(i, 1, n)
    ans += a[i] * (1ll * (rge[i] - i) * (i - lge[i]) -
                   1ll * (rle[i] - i) * (i - lle[i]));
  cout << ans;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
