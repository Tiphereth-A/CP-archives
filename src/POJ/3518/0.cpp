#include <algorithm>
#include <cstdio>
const int N = 1299709 + 5;
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
  int _;
  while (_ = 0, scanf("%d", &_) && _) {
    if (is_pri[_]) {
      puts("0");
      continue;
    }
    int pos = std::lower_bound(pri + 1, pri + cnt + 1, _) - pri - 1;
    printf("%d\n", pri[pos + 1] - pri[pos]);
  }
}
