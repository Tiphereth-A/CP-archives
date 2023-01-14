#include <bits/stdc++.h>
#define N 1050
int c;
char s[N], target[N], now[N], t[N];
int main() {
  gets(s);
  sscanf(strstr(s, "@"), "@yyy loves %s", target);
  while (++c) {
    gets(s);
    int l = strlen(s);
    if (l == 1) break;
    sscanf(s, "yyy loves %s", now);
    if (!strcmp(now, target)) {
      printf("Successful @yyy loves %s attempt\n", target);
      return 0;
    }
    if (std::count(s, s + l, '@') != 1 ||
        (sscanf(strstr(s, "@"), "@yyy loves %s", t), strcmp(t, target))) {
      printf("Unsuccessful @yyy loves %s attempt\n", target);
      printf("%d\n", c + 1);
      printf("yyy loves %s\n", now);
      return 0;
    }
  }
  printf("Unsuccessful @yyy loves %s attempt\n", target);
  printf("%d\n", c);
  printf("Good Queue Shape\n");
  return 0;
}
