#include <bits/stdc++.h>
using namespace std;
const int N = 25005;
bool vis[N];
long long prime[N];
int cnt_prime;
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
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  init_prime();
  int kase;
  cin >> kase;
  while (kase--) {
    int n;
    cin >> n;
    auto x1 = *lower_bound(prime + 1, prime + cnt_prime + 1, n + 1),
         x2 = *lower_bound(prime + 1, prime + cnt_prime + 1, n + x1);
    cout << x1 * x2 << '\n';
  }
  return 0;
}
