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
    return 0;                    \
  }
#define _dis_ans(a, b) _ans(dis(a, b))
int d[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  _for(__, 0, 141, n) {
    cin >> n;
    _for(i, 1, n) cin >> d[i];
    int cnt_leaves = 0;
    _for(i, 1, n) cnt_leaves += d[i] == 1;
    if (n == 1) _ans(0);
    if (cnt_leaves == 2) {
      int a = 0;
      _for(i, 1, n)
        if (d[i] == 1) {
          if (a) _dis_ans(a, i);
          a = i;
        }
    }
    if (cnt_leaves * 2 + __ < 142) {
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
  return 0;
}
