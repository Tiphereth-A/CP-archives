#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, m;
  cin >> n >> m;
  int cnt1 = 0, cnt2 = 0;
  map<pii, char> maps;
  _for(i, 1, m) {
    char op;
    int x, y;
    cin >> op;
    if (op == '+') {
      cin >> x >> y >> op;
      maps[make_pair(x, y)] = op;
      if (maps[make_pair(y, x)]) ++cnt1;
      if (maps[make_pair(y, x)] == op) ++cnt2;
    } else if (op == '-') {
      cin >> x >> y;
      if (maps[make_pair(y, x)]) --cnt1;
      if (maps[make_pair(y, x)] == maps[make_pair(x, y)]) --cnt2;
      maps[make_pair(x, y)] = 0;
    } else {
      cin >> x;
      cout << ((x & 1 ? cnt1 : cnt2) ? "YES" : "NO") << '\n';
    }
  }
  return 0;
}
