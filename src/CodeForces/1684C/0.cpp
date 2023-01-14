#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
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
#define _run_continue(expressions) \
  {                                \
    expressions;                   \
    continue;                      \
  }
int n, m;
vector<int> maps, sorted;
vector<int>::iterator _get(vector<int> &v, int x, int y) {
  return v.begin() + (x * m + y);
}
void _swap(int l, int r) {
  _for(i, 0, n - 1) iter_swap(_get(maps, i, l), _get(maps, i, r));
}
auto solve() -> void {
  cin >> n >> m;
  maps.clear();
  maps.reserve(n * m);
  _for(i, 1, n * m, t) {
    cin >> t;
    maps.push_back(t);
  }
  if (m == 1) _run_return_void(cout << "1 1\n");
  sorted = maps;
  _for(i, 0, n - 1) sort(_get(sorted, i, 0), _get(sorted, i, m));
  bool swapped = 0, invalid = 0;
  int l = 0, r = 0;
  _for(i, 0, n - 1) {
    if (invalid || swapped) break;
    if (is_sorted(_get(maps, i, 0), _get(maps, i, m))) continue;
    _for(j, 0, m - 1) {
      if (*_get(maps, i, j) == *_get(sorted, i, j)) continue;
      if (!l) _run_continue(l = j + 1);
      if (!r) _run_continue(r = j + 1);
      _run_break(invalid = 1);
    }
    if (l && r) {
      swapped = 1;
      _swap(l - 1, r - 1);
    }
  }
  if (!invalid && swapped)
    _for(i, 0, n - 1)
      if (!is_sorted(_get(maps, i, 0), _get(maps, i, m)))
        _run_break(invalid = 1);
  if (invalid) _run_return_void(cout << "-1\n");
  if (!l) l = r = 1;
  cout << l << ' ' << r << '\n';
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
