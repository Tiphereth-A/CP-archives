#include <bits/stdc++.h>
using namespace std;
typedef unsigned u32;
u32 seed;
u32 getnext() {
  seed ^= seed << 13;
  seed ^= seed >> 17;
  seed ^= seed << 5;
  return seed;
}
const int N = 2e7 + 5;
u32 b[N];
u32 prime[N / 10], cnt;
bool vis[N];
int main() {
  int n;
  cin >> n >> seed;
  for (int i = 2; i <= n; ++i) {
    if (!vis[i]) prime[++cnt] = i;
    for (int j = 1; j <= cnt && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      if (i % prime[j] == 0) break;
    }
  }
  for (int i = 1; i <= n; ++i) b[i] = getnext();
  for (int i = 1; i <= cnt; ++i)
    for (int j = 1; j * prime[i] <= n; ++j) b[j * prime[i]] += b[j];
  u32 ans = 0;
  for (int i = 1; i <= n; ++i) ans ^= b[i];
  cout << ans;
  return 0;
}
