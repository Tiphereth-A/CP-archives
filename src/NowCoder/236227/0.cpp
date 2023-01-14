#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const int N = 1e5 + 5, MOD = 114514919810;
string p[N];
auto solve() -> void {
  int n;
  cin >> n;
  string s;
  int id;
  _for(i, 1, n) {
    cin >> s >> id;
    p[id] = s;
  }
  _for(i, 1, n) cout << p[i] << " \n"[p[i] == "." || p[i] == "!"];
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
