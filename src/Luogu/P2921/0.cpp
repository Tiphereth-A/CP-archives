#include <bits/stdc++.h>
using namespace std;
const int N = 100000 + 5;
int nxt[N], color[N], suc[N], dfn[N], minc[N];
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> nxt[i];
  for (int cow = 1; cow <= n; ++cow) {
    for (int i = cow, cnt = 0;; i = nxt[i], ++cnt) {
      if (!color[i]) {
        color[i] = cow;
        dfn[i] = cnt;
      } else if (color[i] == cow) {
        minc[cow] = cnt - dfn[i];
        suc[cow] = dfn[i];
        cout << cnt << '\n';
        break;
      } else {
        minc[cow] = minc[color[i]];
        suc[cow] = cnt + max(suc[color[i]] - dfn[i], 0);
        cout << suc[cow] + minc[cow] << '\n';
        break;
      }
    }
  }
  return 0;
}
