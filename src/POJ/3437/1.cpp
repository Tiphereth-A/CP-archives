#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
int h1 = 0, h2 = 0, u = 0;
char s[200005];
int read() {
  char ch = getchar();
  int f = 1, t = 0;
  while (ch < '0' || ch > '9') {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while ('0' <= ch && ch <= '9') {
    t = t * 10 + ch - '0';
    ch = getchar();
  }
  return t * f;
}
void dfs(int x, int y) {
  int son = 0;
  while (s[u] == 'd') {
    u++;
    son++;
    dfs(x + 1, y + son);
  }
  u++;
  h1 = std::max(h1, x);
  h2 = std::max(h2, y);
}
int main() {
  int T = 0;
  scanf("%s", s);
  while (s[0] != '#') {
    h1 = h2 = u = 0;
    dfs(0, 0);
    printf("Tree %d: %d => %d\n", ++T, h1, h2);
    scanf("%s", s);
  }
}
