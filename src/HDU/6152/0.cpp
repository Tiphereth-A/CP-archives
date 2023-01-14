#include <cstdio>
#include <cstring>
int deg[10];
int main() {
  int kase;
  scanf("%d", &kase);
  while (kase--) {
    memset(deg, 0, sizeof(deg));
    int n;
    scanf("%d", &n);
    if (n >= 6) {
      puts("Bad Team!");
      for (int i = 1; i < n; ++i)
        for (int j = i + 1; j <= n; ++j) scanf("%*d");
      continue;
    }
    int _;
    for (int i = 1; i < n; ++i)
      for (int j = i + 1; j <= n; ++j) {
        scanf("%d", &_);
        if (_) {
          ++deg[i];
          ++deg[j];
        }
      }
    switch (n) {
      case 5:
        if (deg[1] == 2 && deg[2] == 2 && deg[3] == 2 && deg[4] == 2 &&
            deg[5] == 2)
          puts("Great Team!");
        else puts("Bad Team!");
        break;
      case 4:
        if (deg[1] == 3 || deg[1] == 0 || deg[2] == 3 || deg[2] == 0 ||
            deg[3] == 3 || deg[3] == 0 || deg[4] == 3 || deg[4] == 0)
          puts("Bad Team!");
        else puts("Great Team!");
        break;
      case 3:
        if ((deg[1] == 2 && deg[2] == 2 && deg[3] == 2) ||
            (deg[1] == 0 && deg[2] == 0 && deg[3] == 0))
          puts("Bad Team!");
        else puts("Great Team!");
        break;
      default: puts("Great Team!");
    }
  }
}
