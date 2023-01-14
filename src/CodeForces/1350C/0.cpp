#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int prime[N], cnt_prime, d[N], idx_p[N];
bool vis[N];
priority_queue<int, vector<int>, greater<int>> mins[N];
long long gcd(long long a, long long b) { return b == 0 ? a : gcd(b, a % b); }
long long lcm(long long a, long long b) { return a / gcd(a, b) * b; }
int main() {
  for (int i = 2; i < N; ++i) {
    if (!vis[i]) prime[idx_p[i] = ++cnt_prime] = d[i] = i;
    for (int j = 1; j <= cnt_prime; ++j) {
      if (i * prime[j] >= N) break;
      vis[i * prime[j]] = 1;
      d[i * prime[j]] = prime[j];
      if (i % prime[j] == 0) break;
    }
  }
  int n;
  cin >> n;
  if (n == 2) {
    int a, b;
    cin >> a >> b;
    cout << lcm(a, b);
    return 0;
  }
  for (int j = 1, _; j <= n; ++j) {
    cin >> _;
    while (_ > 1) {
      int now_p = d[_], cnt = 0;
      while (_ % now_p == 0) {
        ++cnt;
        _ /= now_p;
      }
      mins[now_p].push(cnt);
    }
  }
  long long ans = 1;
  for (int i = 1, sec_min = 0; i < N; ++i, sec_min = 0) {
    if (mins[i].size() == n) {
      mins[i].pop();
      sec_min = mins[i].top();
    } else if (mins[i].size() == n - 1) sec_min = mins[i].top();
    while (sec_min--) ans *= i;
  }
  cout << ans;
  return 0;
}
