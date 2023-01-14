#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
#define _foreach_cref(i, container) for (const auto &i : container)
#define _set_nul(a) memset(a, 0, sizeof(a))
char c[15];
bool isf[205], vis[15];
int num[205], a[15];
string s[15];
void dfs(int dep, int &cnt, const int &n, const int &l) {
  if (dep == l) {
    _for(i, 0, l - 1) num[c[i]] = a[i];
    int ans = 0, sum = 0;
    _foreach_cref(ch, s[n - 1]) (ans *= 10) += num[ch];
    _for(i, 0, n - 2, _) {
      _ = 0;
      _foreach_cref(ch, s[i]) (_ *= 10) += num[ch];
      sum += _;
      if (sum > ans) return;
    }
    cnt += (sum == ans);
    return;
  }
  _for(i, isf[c[dep]], 9)
    if (!vis[i]) {
      vis[i] = true;
      a[dep] = i;
      dfs(dep + 1, cnt, n, l);
      vis[i] = false;
    }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n;
  while (cin >> n) {
    int l = 0, cnt = 0;
    _set_nul(num);
    _set_nul(vis);
    _set_nul(isf);
    _for(i, 0, n - 1) {
      cin >> s[i];
      _foreach_cref(ch, s[i])
        if (!num[ch]) num[c[l++] = ch] = 1;
      isf[s[i].front()] = true;
    }
    dfs(0, cnt, n, l);
    cout << cnt << '\n';
  }
  return 0;
}
