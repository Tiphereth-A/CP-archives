#include <bits/stdc++.h>
using namespace std;
long long qpow(long long a, long long b, long long mod) {
  long long res = 1;
  for (; b; b >>= 1, (a *= a) %= mod)
    if (b & 1) (res *= a) %= mod;
  return res;
}
const int N = 1e5 + 5;
bool vis[N];
int prime[N], cnt_prime;
void init_prime(int n = N - 1) {
  for (int i = 2; i <= n; ++i) {
    if (!vis[i]) prime[++cnt_prime] = i;
    for (int j = 1; j <= cnt_prime && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      if (i % prime[j] == 0) break;
    }
  }
}
int main() {
  init_prime();
  int x, kase;
  cin >> x >> kase;
  while (kase--) {
    int n;
    cin >> n;
    if (x == 1) {
      if (n & 1 && n > 1) {
        cout << "0" << endl;
        continue;
      }
      cout << "2";
      for (int i = 1; i <= n; ++i) cout << " " << (i & 1 ? n + 1 - i : i - 1);
      cout << endl;
    } else {
      if (vis[n] ^ (n == 4)) {
        cout << "0" << endl;
        continue;
      }
      if (n == 1) {
        cout << "2 1" << endl;
        continue;
      }
      if (n == 4) {
        cout << "2 1 3 2 4" << endl;
        continue;
      }
      cout << "2";
      for (long long i = 1, _ = 1, prod = 1; i < n; ++i) {
        cout << " " << _;
        _ = 1ll * (i + 1) * qpow(prod, n - 2, n) % n;
        (prod *= _) %= n;
      }
      cout << " " << n << endl;
    }
  __end_kase:;
  }
  return 0;
}
