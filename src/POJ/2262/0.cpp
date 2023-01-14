#include <cstdio>
const int N = 1e6 + 5, M = 1e5 + 5;
int vis[N], is_pri[N];
int pri[N], cnt;
int main() {
  for (int i = 2; i < N; ++i) {
    if (!vis[i]) {
      vis[i] = is_pri[i] = 1;
      pri[++cnt] = i;
      for (long long j = 2; j * i < N; ++j) ++vis[j * i];
    }
  }
  int _ = 0;
  while (scanf("%d", &_) && _) {
    for (int i = 2; i <= cnt && pri[i] < _ - 1; ++i) {
      if (is_pri[_ - pri[i]]) {
        printf("%d = %d + %d\n", _, pri[i], _ - pri[i]);
        break;
      }
    }
  }
}
