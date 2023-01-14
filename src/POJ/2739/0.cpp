#include <cstdio>
int vis[10005];
int pri[2000], cnt;
int main() {
  for (int i = 2; i <= 10000; ++i) {
    if (!vis[i]) {
      vis[i] = 1;
      pri[++cnt] = i;
      for (int j = 2; j * i <= 10000; ++j) ++vis[j * i];
    }
  }
  int _ = 0;
  while (scanf("%d", &_) && _) {
    int ans = 0;
    for (int i = 1; i <= cnt && pri[i] <= _; ++i) {
      int sum = 0;
      for (int j = i; sum <= _; j++) {
        sum += pri[j];
        if (sum == _) ++ans;
      }
    }
    printf("%d\n", ans);
  }
}
