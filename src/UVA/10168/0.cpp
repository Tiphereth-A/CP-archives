#include <cstdio>
const int N = 1e7 + 5;
bool vis[N], is_pri[N];
int pri[N], cnt;
int main() {
  for (int i = 2; i < N; ++i) {
    if (!vis[i]) {
      vis[i] = is_pri[i] = 1;
      pri[++cnt] = i;
      for (long long j = 2; j * i < N; ++j) vis[j * i] = 1;
    }
  }
  int _ = 0;
  while (_ = 0, scanf("%d", &_) && _) {
    if (_ < 8) {
      puts("Impossible.");
      continue;
    }
    if (_ < 13) {
      if (_ == 8) puts("2 2 2 2");
      else if (_ == 9) puts("2 2 2 3");
      else if (_ == 10) puts("2 2 3 3");
      else if (_ == 11) puts("2 3 3 3");
      else puts("3 3 3 3");
      continue;
    }
    if (_ % 2) {
      printf("2 3 ");
      _ -= 5;
    } else {
      printf("2 2 ");
      _ -= 4;
    }
    for (int i = 1; i <= cnt && pri[i] < _ - 1; ++i) {
      if (is_pri[_ - pri[i]]) {
        printf("%d %d\n", pri[i], _ - pri[i]);
        break;
      }
    }
  }
}
