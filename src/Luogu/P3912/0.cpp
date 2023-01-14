#include <bits/stdc++.h>
using std::cin;
using std::cout;
const int N = 1e8 + 5;
bool vis[N];
int n, prime[N], cnt_prime;
int main() {
  cin >> n;
  for (int i = 2; i <= n; ++i) {
    if (!vis[i]) prime[++cnt_prime] = i;
    for (int j = 1; j <= cnt_prime && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      if (i % prime[j] == 0) break;
    }
  }
  cout << cnt_prime;
  return 0;
}
