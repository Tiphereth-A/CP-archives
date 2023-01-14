#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _run_continue(expressions) \
  {                                \
    expressions;                   \
    continue;                      \
  }
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const uint32_t OFFSET = 5;
const uint32_t N = 2e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
int unq_cnt_a[N], unq_cnt_b[N];
vector<int> unq_a, unq_b;
set<int> s;
#define __init__(x)                                                \
  unq_##x.reserve(n);                                              \
  _for(i, 1, n, _) {                                               \
    cin >> _;                                                      \
    s.insert(_);                                                   \
    unq_cnt_##x[i] = s.size();                                     \
    if (unq_cnt_##x[i] > unq_cnt_##x[i - 1]) unq_##x.push_back(_); \
  }
bool ans[N];
auto __ins__ = [](int x) {
  if (s.count(x)) s.erase(x);
  else s.insert(x);
};
auto solve() -> void {
  int n;
  cin >> n;
  __init__(a);
  s.clear();
  __init__(b);
  s.clear();
  _for(i, 1, min(unq_a.size(), unq_b.size())) {
    __ins__(unq_a[i - 1]);
    __ins__(unq_b[i - 1]);
    ans[i] = !s.size();
  }
  int q;
  cin >> q;
  _for(i, 1, q, x, y) {
    cin >> x >> y;
    if (unq_cnt_a[x] != unq_cnt_b[y]) _run_continue(cout << "No\n");
    cout << (ans[unq_cnt_a[x]] ? "Yes\n" : "No\n");
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
