#include <bits/stdc++.h>
char s[100005];
int next[100005];
int main() {
  while (~scanf("%s", s + 1)) {
    int n = strlen(s + 1);
    int last = 0, now = 0;
    next[0] = 0;
    for (int i = 1; i <= n; ++i) switch (s[i]) {
        case '[': now = 0; break;
        case ']': now = last; break;
        default:
          next[i] = next[now];
          next[now] = i;
          if (now == last) last = i;
          now = i;
      }
    for (int i = next[0]; i; i = next[i]) printf("%c", s[i]);
    puts("");
  }
  return 0;
}
