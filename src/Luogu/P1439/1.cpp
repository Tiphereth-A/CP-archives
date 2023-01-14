#include <bits/stdc++.h>
const int N = 1e5 + 5;
#define _for(i, l, r) for (auto(i) = (l); (i) <= (r); ++(i))
int n, s[N], t[N], map[N];
int f[N], len;
int main() {
  scanf("%d", &n);
  _for(i, 1, n) {
    scanf("%d", s + i);
    map[s[i]] = i;
  }
  _for(i, 1, n) {
    scanf("%d", t + i);
    t[i] = map[t[i]];
    f[i] = 0x7fffffff;
  }
  f[0] = 0;
  int len = 0;
  _for(i, 1, n) {
    int l = 0, r = len, mid;
    if (t[i] > f[len]) f[++len] = t[i];
    else {
      while (l < r) {
        mid = ((r - l) >> 1) + l;
        if (f[mid] > t[i]) r = mid;
        else l = mid + 1;
      }
      f[l] = std::min(t[i], f[l]);
    }
  }
  printf("%d", len);
}
