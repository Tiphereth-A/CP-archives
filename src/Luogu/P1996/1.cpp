#include <bits/stdc++.h>
#define N 205
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
bool v[N];
int main() {
  int n, m, tot = 0;
  scanf("%d%d", &n, &m);
  _for(i, 1, n) {
    _for(j, 1, m) {
      if (++tot > n) tot = 1;
      if (v[tot]) j--;
    }
    printf("%d ", tot);
    v[tot] = 1;
  }
  return 0;
}
