#include <cstdio>
int main() {
  int t, cnt = 0;
  while (scanf("%d", &t), t) {
    printf("S-Tree #%d:\n", ++cnt);
    int x[10];
    for (int i = 1; i <= t; ++i) scanf("%*cx%d", &x[i]);
    char stree[130] = {0};
    scanf("\n");
    fgets(stree, sizeof(stree) - 1, stdin);
    int n;
    scanf("%d\n", &n);
    char vva[10];
    while (n--) {
      fgets(vva + 1, sizeof(vva) - 1, stdin);
      int sum = 0;
      for (int i = 1; i <= t; ++i) (sum <<= 1) |= (vva[x[i]] & 1);
      printf("%c", stree[sum]);
    }
    puts("\n");
  }
}
