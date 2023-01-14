#include <bits/stdc++.h>
#define _for(i, a, b) for (int i = (a); i <= (b); ++i)
int read() {
  int x = 0, f = 1;
  char c = getchar();
  while (c < '0' || c > '9') {
    if (c == '-') f = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    (x *= 10) += c - '0';
    c = getchar();
  }
  return x * f;
}
int t, s1[256], s2[256];
int main() {
  t = read();
  while (t--) {
    memset(s1, 0, sizeof(s1));
    memset(s2, 0, sizeof(s2));
    char c = getchar();
    while (c != '\n') {
      s1[c]++;
      c = getchar();
    }
    c = getchar();
    while (c != '\n' && c != EOF) {
      s2[c]++;
      c = getchar();
    }
    bool f = 1;
    _for(i, 0, 255)
      if (s1[i] != s2[i]) {
        f = 0;
        puts("GJX is unhappy");
        break;
      }
    if (f) puts("GJX is happy");
  }
  return 0;
}
