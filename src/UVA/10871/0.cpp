#include <algorithm>
#include <cstdio>
const int N = 1e6 + 5, M = 1e4 + 5;
bool vis[N], is_pri[N];
int pri[N], cnt;
int k[M];
long long sum[M];
int main() {
  for (int i = 2; i < N; ++i) {
    if (!vis[i]) {
      vis[i] = is_pri[i] = 1;
      pri[++cnt] = i;
      for (long long j = 2; j * i < N; ++j) vis[j * i] = 1;
    }
  }
  int kase;
  scanf("%d", &kase);
  while (kase--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
      scanf("%d", k + i);
      sum[i] = sum[i - 1] + k[i];
    }
    bool ok = 0;
    for (int len = 2; len <= n; ++len)
      for (int j = 1; len + j - 1 <= n; ++j)
        if (is_pri[sum[len + j - 1] - sum[j - 1]]) {
          ok = 1;
          printf("Shortest primed subsequence is length %d:", len);
          for (int i = 0; i < len; ++i) printf(" %d", k[j + i]);
          puts("");
          goto _1;
        }
  _1:
    if (!ok) puts("This sequence is anti-primed.");
  }
}
