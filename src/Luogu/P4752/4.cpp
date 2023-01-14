#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
std::priority_queue<i64> a, b;
int main() {
  i64 t, tmp, tmpa, tmpb;
  scanf("%lld", &t);
  while (t--) {
    i64 m, n, f = 0;
    scanf("%lld%lld", &n, &m);
    tmp = tmpa = tmpb = 0;
    _for(i, 1, n) {
      scanf("%lld", &tmp);
      if (tmp == 1) {
        --i;
        --n;
      } else a.push(tmp);
    }
    _for(i, 1, m) {
      scanf("%lld", &tmp);
      if (tmp == 1) {
        --i;
        --m;
      } else b.push(tmp);
    }
    if (f == 1 || n - m != 1 || n == 0) {
      puts("NO");
      continue;
    }
    i64 p = 0;
    _for(i, 1, m) {
      tmpa = a.top();
      tmpb = b.top();
      if (tmpa != tmpb) {
        p = tmpa;
        break;
      }
      a.pop();
      b.pop();
    }
    if (!p) p = a.top();
    i64 sq = sqrt(p);
    _for(i, 2, sq)
      if (p % i == 0) {
        f = -1;
        break;
      }
    puts(f == -1 ? "NO" : "YES");
  }
  return 0;
}
