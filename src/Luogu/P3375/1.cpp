#include <bits/stdc++.h>
char s[1000001], p[1000001];
int sLen, pLen, next[1000001] = {-1};
int main() {
  scanf("%s\n%s", s, p);
  sLen = strlen(s);
  pLen = strlen(p);
  int i = 0, j = -1;
  while (i < pLen) {
    if (j == -1 || p[i] == p[j]) next[++i] = ++j;
    else j = next[j];
  }
  i = j = 0;
  while (i < sLen && j < pLen) {
    if (j == -1 || s[i] == p[j]) {
      ++i;
      ++j;
    } else j = next[j];
    if (j == pLen) {
      printf("%d\n", i - j + 1);
      j = next[j];
    }
  }
  for (i = 1; i <= pLen; ++i) printf("%d ", next[i]);
  return 0;
}
