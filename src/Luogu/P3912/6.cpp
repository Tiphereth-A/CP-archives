#include <bits/stdc++.h>
using u64 = uint64_t;
const int N = 350050;
bool vis[N];
int prime[N / 10], cnt_prime, ans[N], n, sqrt_n, last[N << 1], cnt_val_div_n;
u64 dp[N << 1], val_div_n[N << 1];
int main() {
  scanf("%llu", &n);
  sqrt_n = sqrt(n);
  for (int i = 2; i <= sqrt_n; ++i) {
    ans[i] = ans[i - 1];
    if (!vis[i]) {
      prime[++cnt_prime] = i;
      ++ans[i];
    }
    for (int j = 1; j <= cnt_prime && (u64)i * prime[j] <= sqrt_n; ++j) {
      vis[i * prime[j]] = true;
      if (i % prime[j] == 0) break;
    }
  }
  for (u64 i = n; i; i = n / (n / i + 1)) val_div_n[++cnt_val_div_n] = n / i;
  for (int i = 1; i <= cnt_val_div_n; ++i) dp[i] = val_div_n[i];
  u64 k;
  for (int i = 1; i <= cnt_prime; ++i)
    for (int j = cnt_val_div_n; j; --j) {
      if ((k = val_div_n[j] / prime[i]) < prime[i]) break;
      k = k < sqrt_n ? k : cnt_val_div_n - n / k + 1;
      dp[j] -= dp[k] - ((last[j] = i) - last[k] - 1);
    }
  printf("%llu", ans[sqrt_n] + dp[cnt_val_div_n] - 1);
  return 0;
}
