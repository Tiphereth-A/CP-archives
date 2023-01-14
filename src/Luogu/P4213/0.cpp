#include <bits/stdc++.h>
using namespace std;
const int N = 5e6 + 5;
i64 mu[N];
unordered_map<int, i64> sum_mu;
u64 phi[N];
unordered_map<int, u64> sum_phi;
i64 get_sum_mu(int n) {
  if (n < N) return mu[n];
  if (sum_mu[n]) return sum_mu[n];
  i64 ans = 1;
  for (i64 l = 2, r; l <= n; l = r + 1) {
    r = n / (n / l);
    ans -= (r - l + 1) * get_sum_mu(n / l);
  }
  return sum_mu[n] = ans;
}
u64 get_sum_phi(int n) {
  if (n < N) return phi[n];
  if (sum_phi[n]) return sum_phi[n];
  u64 ans = (u64)n * (n + 1) / 2;
  for (i64 l = 2, r; l <= n; l = r + 1) {
    r = n / (n / l);
    ans -= (u64)(r - l + 1) * get_sum_phi(n / l);
  }
  return sum_phi[n] = ans;
}
int prime[N / 10], cnt;
bool vis[N];
int main() {
  phi[1] = mu[1] = 1;
  for (int i = 2; i < N; ++i) {
    if (!vis[i]) {
      prime[++cnt] = i;
      mu[i] = -1;
      phi[i] = i - 1;
    }
    for (int j = 1; j <= cnt && i * prime[j] < N; ++j) {
      vis[i * prime[j]] = 1;
      mu[i * prime[j]] = i % prime[j] ? -mu[i] : 0;
      phi[i * prime[j]] = phi[i] * (i % prime[j] ? phi[prime[j]] : prime[j]);
      if (i % prime[j] == 0) break;
    }
  }
  for (int i = 2; i < N; ++i) {
    mu[i] += mu[i - 1];
    phi[i] += phi[i - 1];
  }
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    cout << get_sum_phi(n) << " " << get_sum_mu(n) << endl;
  }
  return 0;
}
