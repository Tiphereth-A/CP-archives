#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define gc getchar
using namespace std;
const int N = 105;
int r, c, k, ans;
char g[N][N];
int main() {
  scanf("%d%d%d", &r, &c, &k);
  gc();
  _for(i, 1, r)
    _for(j, 1, c) cin >> g[i][j];
  _for(i, 1, c) {
    int cnt = 0;
    _for(j, 1, r + 1) {
      if (g[j][i] == '.') cnt++;
      else {
        if (cnt >= k) ans += cnt - k + 1;
        cnt = 0;
      }
    }
  }
  _for(i, 1, r) {
    int cnt = 0;
    _for(j, 1, c + 1) {
      if (g[i][j] == '.') cnt++;
      else {
        if (cnt >= k) ans += cnt - k + 1;
        cnt = 0;
      }
    }
  }
  printf("%d", ((k == 1) ? (ans >> 1) : (ans)));
  return 0;
}
