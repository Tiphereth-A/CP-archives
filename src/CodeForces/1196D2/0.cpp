#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
const char s[] = "RGB";
int cnt[3][N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int kase;
  cin >> kase;
  while (kase--) {
    int n, k;
    cin >> n >> k;
    string str;
    cin >> str;
    _for(i, 0, 2)
      _for(j, 1, n)
        cnt[i][j] = cnt[i][j - 1] + (str[j - 1] != s[(i + j - 1) % 3]);
    int ans = n;
    _for(i, 0, 2)
      _for(j, k, n) ans = min(ans, cnt[i][j] - cnt[i][j - k]);
    cout << ans << '\n';
  }
  return 0;
}
