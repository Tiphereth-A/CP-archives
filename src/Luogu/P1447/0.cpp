#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int prime[N], cnt;
bool vis[N];
i64 sphi[N];
void seive(int n = N - 5) {
  sphi[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!vis[i]) sphi[prime[++cnt] = i] = i - 1;
    for (int j = 1; j <= cnt && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      sphi[i * prime[j]] = sphi[i] * prime[j];
      if (i % prime[j] == 0) break;
      sphi[i * prime[j]] -= sphi[i];
    }
  }
  for (int i = 2; i <= n; ++i) sphi[i] += sphi[i - 1];
}
int main() {
  seive();
  i64 m, n;
  cin >> m >> n;
  if (m > n) swap(m, n);
  i64 ans = 0;
  for (i64 l = 1, r; l <= m; l = r + 1) {
    r = min(n / (n / l), m / (m / l));
    ans += (n / l) * (m / l) * (sphi[r] - sphi[l - 1]);
  }
  cout << 2 * ans - n * m << endl;
}
