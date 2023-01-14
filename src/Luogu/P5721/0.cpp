#include <bits/stdc++.h>
int main() {
  int n;
  scanf("%d", &n);
  int cnt = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; ++j) printf("%02d", ++cnt);
    puts("");
  }
}
