#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n;
  cin >> n;
  vector<int> a;
  multiset<int> s;
  _for(i, 1, n, _) {
    cin >> _;
    a.push_back(_);
  }
  _for(i, 1, n, _) {
    cin >> _;
    s.insert(_);
  }
  for (const int &i : a) {
    auto it = s.lower_bound((n - i) % n);
    cout << (*((it != s.end()) ? it : s.begin()) + i) % n << ' ';
    s.erase((it != s.end()) ? it : s.begin());
  }
}
