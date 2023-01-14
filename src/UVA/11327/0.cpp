#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int N = 2e5 + 5, P = 2e4 + 5;
bool vis[N];
int prime[P], cnt_prime;
int64_t phi[N];
void init_prime(const int &n = N - 1) {
  phi[0] = phi[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!vis[i]) {
      prime[++cnt_prime] = i;
      phi[i] = i - 1;
    }
    for (int j = 1; j <= cnt_prime && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      phi[i * prime[j]] = phi[i] * prime[j];
      if (i % prime[j] == 0) break;
      phi[i * prime[j]] -= phi[i];
    }
  }
  for (int i = 1; i <= n; ++i) phi[i] += phi[i - 1];
}
template <typename T>
T gcd(T n, T m) {
  while (m ^= n ^= m ^= n %= m);
  return n;
}
int main() {
  init_prime();
  i64 x;
  while ((cin >> x), x) {
    if (x == 1) {
      cout << "0/1\n";
      continue;
    }
    if (x == 2) {
      cout << "1/1\n";
      continue;
    }
    ptrdiff_t idx = upper_bound(phi, phi + N, x) - phi - 1;
    if (!(x -= phi[idx++])) {
      cout << idx - 2 << '/' << idx - 1 << '\n';
      continue;
    }
    i64 i;
    for (i = 1; x; ++i) x -= gcd(i, idx) == 1;
    cout << i - 1 << '/' << idx << '\n';
  }
  return 0;
}
