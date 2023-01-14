#include <algorithm>
#include <cstdio>
const int N = 1e4 + 5;
int a[N];
int main() {
  int kase;
  scanf("%d", &kase);
  while (kase--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    int q;
    scanf("%d", &q);
    for (int i = 1, _; i <= q; ++i) {
      scanf("%d", &_);
      int now = 1, pre = 1;
      while (_ != a[now])
        if (_ > a[now]) {
          putchar('W');
          pre = now;
          while (a[pre] >= a[now] && now < n) ++now;
        } else if (_ < a[now]) {
          putchar('E');
          pre = now;
          while (a[pre] <= a[now] && now < n) ++now;
        }
      puts("");
    }
  }
}
