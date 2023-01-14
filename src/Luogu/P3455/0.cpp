#include <bits/stdc++.h>
using namespace std;
const int N = 5e4 + 5;
int prime[N], cnt;
bool vis[N];
i64 smu[N];
void seive(int n = N - 5) {
  smu[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!vis[i]) {
      prime[++cnt] = i;
      smu[i] = -1;
    }
    for (int j = 1; j <= cnt && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      if (i % prime[j] == 0) { break; }
      smu[i * prime[j]] = -smu[i];
    }
  }
  for (int i = 2; i <= n; ++i) smu[i] += smu[i - 1];
}
int main() {
  seive();
  int _t;
  cin >> _t;
  while (_t--) {
    i64 m, n, k;
    cin >> m >> n >> k;
    if (m > n) swap(m, n);
    i64 ans = 0;
    for (i64 l = 1, r; l <= m; l = r + 1) {
      r = min(n / (n / l), m / (m / l));
      ans += (n / l / k) * (m / l / k) * (smu[r] - smu[l - 1]);
    }
    cout << ans << endl;
  }
}
