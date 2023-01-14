#include <bits/stdc++.h>
using namespace std;
bool a[100][100];
int b[10000];
int n;
int f(int l) {
  int u = 0;
  switch (l) {
    case 1:
      for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) ((u += a[i][j]) *= 1091) %= 1000151;
      break;
    case 2:
      for (int i = n; i; --i)
        for (int j = 1; j <= n; ++j) ((u += a[j][i]) *= 1091) %= 1000151;
      break;
    case 3:
      for (int i = n; i; --i)
        for (int j = n; j; --j) ((u += a[i][j]) *= 1091) %= 1000151;
      break;
    case 4:
      for (int i = 1; i <= n; ++i)
        for (int j = n; j; --j) ((u += a[j][i]) *= 1091) %= 1000151;
      break;
  }
  return u;
}
int main() {
  while (~scanf("%d", &n) && n) {
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    int ans = 0;
    char k;
    for (int i = 1, s, d; i <= 2 * n; ++i) {
      scanf("%d%d %c\n", &s, &d, &k);
      if (ans) continue;
      a[s][d] = k == '+';
      b[i] = f(1);
      for (int j = 0; j < i; ++j)
        if (b[j] == f(1) || b[j] == f(2) || b[j] == f(3) || b[j] == f(4)) {
          ans = i;
          break;
        }
    }
    if (!ans) puts("Draw");
    else printf("Player %d wins on move %d\n", 1 + ans % 2, ans);
  }
}
