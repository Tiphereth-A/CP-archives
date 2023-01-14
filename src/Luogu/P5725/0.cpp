#include <bits/stdc++.h>
int main() {
  int n;
  scanf("%d", &n);
  int cnt = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) printf("%02d", ++cnt);
    puts("");
  }
  puts("");
  cnt = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = n; j; --j)
      if (j <= i) printf("%02d", ++cnt);
      else printf("  ");
    puts("");
  }
}
