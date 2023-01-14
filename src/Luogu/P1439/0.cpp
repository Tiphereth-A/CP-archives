#include <bits/stdc++.h>
#define N 100005
#define _for(i, l, r) for (int(i) = (l); (i) <= (r); ++(i))
#define Min(a, b) (((a) > (b)) ? (b) : (a))
int a[N], b[N], m[N], f[N], n;
int main() {
  scanf("%d", &n);
  _for(i, 1, n) {
    scanf("%d", a + i);
    m[a[i]] = i;
  }
  _for(i, 1, n) {
    scanf("%d", b + i);
    b[i] = m[b[i]];
    f[i] = 0x7fffffff;
  }
  f[0] = 0;
  int len = 0;
  _for(i, 1, n) {
    int l = 0, r = len, mid;
    if (b[i] > f[len]) f[++len] = b[i];
    else {
      while (l < r) {
        mid = ((r - l) >> 1) + l;
        if (f[mid] > b[i]) r = mid;
        else l = mid + 1;
      }
      f[l] = Min(b[i], f[l]);
    }
  }
  printf("%d", len);
}
