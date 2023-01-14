#include <bits/stdc++.h>
using namespace std;
const int N = 5e4 + 5;
int mu[N] = {0, 1}, prime[N], cnt;
bool vis[N];
i64 sum_mu[N] = {0, 1}, div_block[N] = {0, 1};
int main() {
  for (int i = 2; i < N; ++i) {
    if (!vis[i]) {
      prime[++cnt] = i;
      mu[i] = -1;
    }
    for (int j = 1; j <= cnt && i * prime[j] < N; ++j) {
      vis[i * prime[j]] = 1;
      if (i % prime[j] == 0) {
        mu[i * prime[j]] = 0;
        break;
      }
      mu[i * prime[j]] = -mu[i];
    }
  }
  for (int i = 2; i < N; ++i) sum_mu[i] = sum_mu[i - 1] + mu[i];
  for (int i = 2; i < N; ++i)
    for (int l = 1, r; l <= i; l = r + 1) {
      r = i / (i / l);
      div_block[i] += (r - l + 1) * (i / l);
    }
  int kase;
  cin >> kase;
  while (kase--) {
    int n, m;
    cin >> n >> m;
    i64 ans = 0;
    if (n > m) swap(n, m);
    for (int l = 1, r; l <= n; l = r + 1) {
      r = min(n / (n / l), m / (m / l));
      ans += (sum_mu[r] - sum_mu[l - 1]) * div_block[n / l] * div_block[m / l];
    }
    cout << ans << endl;
  }
  return 0;
}
