#include <bits/stdc++.h>
char words[205];
int n;
int main() {
  while (~scanf("%d", &n))
    while (n--) {
      scanf("%s", words);
      int len = strlen(words);
      for (int k, i = 1; i <= len; ++i)
        if (len % i == 0) {
          for (k = i; k < len; ++k)
            if (words[k] != words[k % i]) break;
          if (k == len) {
            printf("%d\n", i);
            break;
          }
        }
      if (n) puts("");
    }
  return 0;
}
