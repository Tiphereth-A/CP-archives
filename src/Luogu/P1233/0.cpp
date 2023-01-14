#include <bits/stdc++.h>
#define N 5005
#define _for(i, l, r) for (int(i) = (l); (i) <= (r); ++(i))
#define _read_int(a)
do {
  char ch;
  while ((a = getchar()) > '9' || a < '0');
  for (a -= '0'; (ch = getchar()) >= '0' && ch <= '9';
       a = (a << 3) + (a << 1) + ch - '0');
} while (0) struct node {
  int l, w;
  bool operator<(const node &b) const {
    return (l == b.l) ? (w > b.w) : (l > b.l);
  }
} a[N];
int n, f[N], ans;
int main() {
  _read_int(n);
  _for(i, 1, n) {
    _read_int(a[i].l);
    _read_int(a[i].w);
  }
  std::sort(a + 1, a + n + 1);
  _for(i, 1, n) {
    int tmp = a[i].w;
    if (tmp > f[ans]) f[++ans] = tmp;
    else {
      int l = 1, r = ans, mid;
      while (l < r) {
        mid = ((r - l) >> 1) + l;
        (f[mid] >= tmp) ? (r = mid) : (l = mid + 1);
      }
      f[l] = tmp;
    }
  }
  printf("%d", ans);
  return 0;
}
