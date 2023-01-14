#include <cstdio>
#include <cstring>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define pc putchar
#define N 105
int t;
char s[N];
bool cmp(int len, int a, int b) {
  _for(i, 0, len - 1)
    if (s[(i + a) % len] != s[(i + b) % len])
      return s[(i + a) % len] < s[(i + b) % len];
  return 0;
}
int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%s", s);
    int len = strlen(s), ans = 0;
    _for(i, 1, len - 1)
      if (cmp(len, i, ans)) ans = i;
    _for(i, 0, len - 1) pc(s[(ans + i) % len]);
    pc('\n');
  }
  return 0;
}
