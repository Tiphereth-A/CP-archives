#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using msi = multiset<int>;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
#define _all(a) (a).begin(), (a).end()
vi a;
msi b, c;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, _;
  cin >> n;
  _for(i, 1, n) {
    cin >> _;
    a.push_back(_);
  }
  _for(i, 1, n) {
    cin >> _;
    b.insert(_);
  }
  _for(i, 1, n) {
    cin >> _;
    c.insert(_);
  }
  sort(_all(a));
  auto itb = b.begin(), itc = c.begin();
  int cnt = 0;
  for (int val : a) {
    itb = b.upper_bound(val);
    if (itb == b.end()) continue;
    itc = c.upper_bound(*itb);
    if (itc == c.end()) continue;
    ++cnt;
    b.erase(itb);
    c.erase(itc);
  }
  cout << cnt;
  return 0;
}
