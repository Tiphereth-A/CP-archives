#include <bits/stdc++.h>
char s[10];
int main() {
  fgets(s, 10, stdin);
  int n = strlen(s), ans = 0;
  for (int i = 0; i < n; ++i)
    if (isalnum(s[i])) ++ans;
  printf("%d", ans);
  return 0;
}
