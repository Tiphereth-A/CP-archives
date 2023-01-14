#include <bits/stdc++.h>
using namespace std;
const int N = 1e7 + 5;
bool vis[N];
int prime[N], cnt_prime;
int phi[N];
void init(int n = N - 1) {
  phi[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!vis[i]) phi[prime[++cnt_prime] = i] = i - 1;
    for (int j = 1; j <= cnt_prime && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      phi[i * prime[j]] = phi[i] * prime[j];
      if (i % prime[j] == 0) break;
      phi[i * prime[j]] -= phi[i];
    }
  }
}
i64 sum[N];
int main() {
  i64 n;
  cin >> n;
  init(n);
  for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + phi[i];
  i64 ans = 0;
  for (int i = 1; i <= cnt_prime; ++i) ans += sum[n / prime[i]] * 2 - 1;
  cout << ans;
  return 0;
}
