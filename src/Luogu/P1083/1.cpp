#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define mem(a) memset(a, 0, sizeof(a))
#define N 1000005
int n, m, r[N], s[N], t[N], d[N], diff[N];
bool judge(int x) {
  mem(diff);
  _for(i, 1, x) {
    diff[s[i]] += d[i];
    diff[t[i] + 1] -= d[i];
  }
  int now = 0;
  _for(i, 1, n) {
    now += diff[i];
    if (now > r[i]) return 0;
  }
  return 1;
}
int main() {
  scanf("%d%d", &n, &m);
  _for(i, 1, n) scanf("%d", r + i);
  _for(i, 1, m) scanf("%d%d%d", d + i, s + i, t + i);
  if (judge(m)) {
    puts("0");
    return 0;
  }
  int l = 1, r = m;
  while (l < r) {
    int mid = (l + r) >> 1;
    if (judge(mid)) l = mid + 1;
    else r = mid;
  }
  printf("-1\n%d", l);
  return 0;
}
