#include <bits/stdc++.h>
using namespace std;
const int N = 4e6 + 5;
bool vis[N];
int prime[N], cnt_prime;
int phi[N];
i64 f[N];
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
    f[i] = phi[i];
  }
  for (int i = 2; i <= sqrt(n); ++i) {
    f[i * i] += phi[i] * i;
    for (int j = i + 1; i * j <= n; ++j) f[i * j] += phi[i] * j + phi[j] * i;
  }
  for (int i = 2; i <= n; ++i) f[i] += f[i - 1];
}
int main() {
  init();
  i64 n;
  while ((cin >> n) && n) cout << f[n] << endl;
  return 0;
}
