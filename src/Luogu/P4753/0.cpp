#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _rfor(i, r, l) for (int i = (r); i >= (l); --i)
int m, n, s, w[100010];
int pos, cnt, stp[100010];
bool f[100010];
int main() {
  scanf("%d%d%d", &n, &m, &s);
  _for(i, 1, m) scanf("%d", w + i);
  std::sort(w + 1, w + m + 1);
  w[m + 1] = n;
  _for(i, 1, m + 1) {
    if (w[i] - pos >= s) {
      pos = w[i];
      stp[++cnt] = i;
      f[i] = true;
    }
  }
  if (pos != w[m + 1]) {
    puts("NO");
    return 0;
  }
  _rfor(i, m, 0) {
    if (!f[i] && pos - w[i] >= s) {
      pos = w[i];
      stp[++cnt] = i;
      f[i] = true;
    }
  }
  if (cnt < m + 2) puts("NO");
  else {
    puts("YES");
    _for(i, 1, m + 2) printf("%d%c", stp[i], i == m + 2 ? '\n' : ' ');
  }
  return 0;
}
