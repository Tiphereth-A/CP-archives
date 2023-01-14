#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _all(a) (a).begin(), (a).end()
#define _run_return_void(expressions) \
  {                                   \
    expressions;                      \
    return;                           \
  }
#define _run_break(expressions) \
  {                             \
    expressions;                \
    break;                      \
  }
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
void print(int x, int y) { cout << x + 1 << ' ' << y + 1 << '\n'; }
#define _prev(x) ((x + n - 1) % n)
#define _next(x) ((x + 1) % n)
auto solve() -> void {
  int n;
  cin >> n;
  string s;
  cin >> s;
  auto _ = count_if(_all(s), [](char ch) { return ch & 1; });
  if (!_ || _ % 2) _run_return_void(cout << "NO\n");
  cout << "YES\n";
  int r = 0;
  for (int i = _next(r); i != r; i = _next(i))
    if (s[i] & 1) _run_break(r = i);
  if (s[_prev(r)] & 1) {
    for (int i = _prev(r); i != r; i = _prev(i))
      if (!(s[i] & 1)) _run_break(r = (i + 1) % n);
  }
  if (s[_prev(r)] & 1) _run_return_void(_for(i, 1, n - 1) print(0, i));
  int _r = r;
  bool f1 = 0;
  while (!(s[r] & 1) || (!(s[_prev(r)] & 1) && !(s[_next(r)] & 1))) {
    r = _next(r);
    if (r == _r) _run_break(f1 = 1);
  }
  if (f1) {
    vector<int> odds;
    odds.reserve(_);
    odds.push_back(r);
    for (int i = _next(r); i != r; i = _next(i))
      if (s[i] & 1) odds.push_back(i);
    _for(i, 1, odds.size() - 2) {
      print(r, _next(odds[i - 1]));
      for (int j = _next(_next(odds[i - 1])); j != _next(odds[i]); j = _next(j))
        print(_prev(j), j);
    }
    print(r, _next(odds[odds.size() - 2]));
    for (int j = _next(_next(odds[odds.size() - 2])); j != odds.back();
         j = _next(j))
      print(_prev(j), j);
    print(_prev(odds.back()), _prev(r));
    for (int j = _prev(_prev(r)); j != _prev(odds.back()); j = _prev(j))
      print(_next(j), j);
    return;
  }
  bool f = 0;
  int a = r;
  for (int i = _prev(r); i != r; i = _prev(i)) {
    if (s[i] & 1) {
      if (f) {
        print(a, i);
        f = 0;
      } else print(r, i);
      continue;
    }
    if (!f) {
      f = 1;
      a = i;
      print(a, r);
      continue;
    }
    print(a, i);
    a = i;
  }
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
