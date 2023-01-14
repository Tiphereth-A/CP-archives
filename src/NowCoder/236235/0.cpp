#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
int cnt[256];
auto solve() -> void {
  char ch;
  int n;
  cin >> n;
  _for(i, 1, n) {
    cin >> ch;
    ++cnt[ch];
  }
  int ans = 0;
  char anch = 0;
  _for(i, 0, 255) {
    if (cnt[i] > ans) { ans = cnt[anch = i]; }
  }
  cout << anch;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
