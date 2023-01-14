#include <bits/stdc++.h>
const char *str[4] = {"fantasy", "forward", "backward", "both"};
char s[100005], s1[105], s2[105];
int main() {
  int a = -1, i, j;
  bool b = 0, f1 = 0, f2 = 0;
  scanf("%s%s%s", s, s1, s2);
  for (i = 0; s[i] && a == -1; ++i) {
    b = 1;
    for (j = 0; s1[j] && b; ++j)
      if (s[i + j] != s1[j]) b = 0;
    if (b) a = i + strlen(s1);
  }
  if (a != -1)
    for (i = a; s[i] && !f1; ++i) {
      f1 = 1;
      for (j = 0; s2[j] && f1; ++j)
        if (s[i + j] != s2[j]) f1 = 0;
    }
  a = -1;
  for (i = strlen(s) - 1; i >= 0 && a == -1; --i) {
    b = 1;
    for (j = 0; s1[j] && b; ++j)
      if (s[i - j] != s1[j]) b = 0;
    if (b) a = i - strlen(s1);
  }
  if (a != -1)
    for (i = a; i >= 0 && !f2; --i) {
      f2 = 1;
      for (j = 0; s2[j] && f2; ++j)
        if (s[i - j] != s2[j]) f2 = 0;
    }
  printf("%s", str[f1 + f2 * 2]);
  return 0;
}
