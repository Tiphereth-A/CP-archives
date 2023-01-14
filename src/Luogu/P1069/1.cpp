#include <bits/stdc++.h>
#define INF 2147483647
using namespace std;
struct A {
  int number, count;
} a[101];
int m1, m2, n, top;
int main() {
  scanf("%d%d%d", &n, &m1, &m2);
  int x = m1;
  for (int i = 2; i <= x; i++) {
    if (x % i == 0) {
      a[++top].number = i;
      while (x % i == 0) {
        x /= i;
        a[top].count++;
      }
      a[top].count *= m2;
    }
  }
  int minn = INF;
  for (int i = 1; i <= n; i++) {
    int m;
    scanf("%d", &m);
    bool b = true;
    for (int j = 1; j <= top; j++) b = b && (m % a[j].number == 0);
    if (b) {
      int maxx = 0;
      for (int j = 1; j <= top; j++) {
        int ans = 0, mx = m;
        while (mx % a[j].number == 0) {
          mx /= a[j].number;
          ans++;
        }
        ans = (a[j].count - 1) / ans + 1;
        maxx = max(maxx, ans);
      }
      minn = min(minn, maxx);
    }
  }
  if (minn == INF) printf("-1");
  else printf("%d", minn);
  return 0;
}
