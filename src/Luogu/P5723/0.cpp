#include <bits/stdc++.h>
const int N = 1e5 + 5;
int prime[N], cnt;
bool vis[N];
int main() {
  int n;
  scanf("%d", &n);
  int sum = 0;
  for (int i = 2; i <= n; ++i) {
    if (!vis[i]) {
      sum += prime[++cnt] = i;
      if (sum >= n) {
        if (sum > n) --cnt;
        break;
      }
    }
    for (int j = 1; j <= cnt && i * prime[j] <= n; ++j) {
      vis[i * prime[j]] = 1;
      if (i % prime[j] == 0) break;
    }
  }
  for (int i = 1; i <= cnt; ++i) printf("%d\n", prime[i]);
  printf("%d", cnt);
}
