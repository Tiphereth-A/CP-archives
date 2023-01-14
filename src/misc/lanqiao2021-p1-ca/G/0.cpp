#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (auto i = (l); i <= (r); ++i)
#define _rfor(i, r, l) for (auto i = (r); i >= (l); --i)
const int N = 2e5 + 5;
int x[N];
int main() {
  int kase;
  scanf("%d", &kase);
  while (kase--) {
    int n;
    scanf("%d", &n);
    _for(i, 1, n) scanf("%d", x + i);
    int state = 0;
    _rfor(i, 20, 0) {
      int now = 1 << i;
      int cnt = 0;
      _for(i, 1, n) cnt += !!(x[i] & now);
      if (!(cnt & 1)) continue;
      state = ((n - cnt) & 1) && (cnt != 1) ? -1 : 1;
      break;
    }
    printf("%d\n", state);
  }
}
