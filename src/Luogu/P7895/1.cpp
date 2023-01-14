#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
#define _all(a) (a).begin(), (a).end()
const int OFFSET = 5;
const int N = 5e5 + OFFSET;
int dis(int a, int b) {
  cout << "dis " << a << " " << b << endl;
  int ret;
  cin >> ret;
  return ret;
}
int dfn(int a) {
  cout << "dfn " << a << endl;
  int ret;
  cin >> ret;
  return ret;
}
#define _del cout << "del" << endl
#define _ans(a)                  \
  {                              \
    auto __a = a;                \
    cout << "! " << __a << endl; \
    return;                      \
  }
#define _dis_ans(a, b) _ans(dis(a, b))
int d[N];
int is_chrysanthemun(int n) {
  int root = 0, maxd = 0;
  _for(i, 1, n)
    if (d[i] > maxd) maxd = d[root = i];
  _for(i, 1, n)
    if (i != root && d[i] > 2) return 0;
  return root;
}
void solve() {
  _for(__, 0, 141, n) {
    cin >> n;
    _for(i, 1, n) cin >> d[i];
    int cnt_leaves = 0;
    _for(i, 1, n) cnt_leaves += d[i] == 1;
    if (n == 1) _ans(0);
    if (n == 2) _dis_ans(1, 2);
    if (n == 3) {
      _del;
      _ans(0);
    }
    if (n == 4) {
      _del;
      if (cnt_leaves == 3) _ans(0);
      int a = 0, b = 0;
      _for(i, 1, n)
        if (d[i] > 1) (a ? b : a) = i;
      _dis_ans(a, b);
    }
    if (cnt_leaves == 2) {
      int a = 0;
      _for(i, 1, n)
        if (d[i] == 1) {
          if (a) _dis_ans(a, i);
          a = i;
        }
    }
    if (int root = is_chrysanthemun(n); root && cnt_leaves <= (141 - __) * 2) {
      int a = 0;
      int ans = 0;
      _for(i, 1, n, _)
        if (d[i] == 1) {
          if (a) {
            ans += dis(a, i);
            a = 0;
            continue;
          }
          a = i;
        }
      if (a) ans += dis(root, a);
      _ans(ans);
    }
    if (cnt_leaves * 2 + __ <= 142) {
      vector<pii> _;
      _for(i, 1, n)
        if (d[i] == 1) _.emplace_back(dfn(i), i);
      sort(_all(_));
      int ans = 0;
      for (auto it = _.begin(); it != _.end(); ++it)
        ans += dis(it->second,
                   (it + 1) == _.end() ? _.front().second : (it + 1)->second);
      _ans(ans / 2);
    }
    _del;
  }
  while (1);
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
