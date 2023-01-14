#include <bits/stdc++.h>
using namespace std;
char s[100005];
int last, now, nxt[100005];
int main() {
  while (~scanf("%s", s + 1)) {
    int n = strlen(s + 1);
    last = 0;
    now = 0;
    nxt[0] = 0;
    for (int i = 1; i <= n; i++) {
      char ch = s[i];
      if (ch == '[') now = 0;
      else if (ch == ']') now = last;
      else {
        nxt[i] = nxt[now];
        nxt[now] = i;
        if (now == last) last = i;
        now = i;
      }
    }
    for (int i = nxt[0]; i != 0; i = nxt[i]) printf("%c", s[i]);
    printf("\n");
  }
  return 0;
}
