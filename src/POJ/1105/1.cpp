#include <stdio.h>
const int MAXN = 128 + 10;
char terminal[MAXN];
char outcome[MAXN];
int n;
char order[8];
int amount = 0;
char s[8][2];
char dfs(int height, int loc) {
  if (height == n) return terminal[loc - 1];
  int a = s[height][1] - '0';
  int b = order[a - 1] - '0';
  if (b == 0) return (dfs(height + 1, loc * 2 - 1));
  else return (dfs(height + 1, loc * 2));
}
int main() {
  while (scanf("%d", &n) && n != 0) {
    amount++;
    int i;
    for (i = 0; i < n; i++) scanf("%s", s[i]);
    scanf("%s", terminal);
    int k;
    scanf("%d", &k);
    for (i = 0; i < k; i++) {
      scanf("%s", order);
      outcome[i] = dfs(0, 1);
    }
    printf("S-Tree #%d:\n", amount);
    for (i = 0; i < k; i++) printf("%c", outcome[i]);
    printf("\n");
    printf("\n");
  }
  return 0;
}
