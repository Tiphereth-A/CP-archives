#include <bits/stdc++.h>
using namespace std;
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
typedef pair<int, int> pii;
vector<pii> ans;
queue<int> tmp;
int main() {
  init_prime();
  int n;
  scanf("%d", &n);
  if (n < 4) {
    puts("0");
    return 0;
  }
  memset(vis, 0, sizeof(vis));
  int _ = upper_bound(prime + 1, prime + cnt_prime + 1, n / 2) - prime;
  for (int i = _; i; --i) {
    for (int j = 3; prime[i] * j <= n; ++j)
      if (!vis[prime[i] * j]) {
        tmp.push(prime[i] * j);
        vis[prime[i] * j] = 1;
      }
    if (tmp.size() % 2 == 0 && 2 * prime[i] <= n && !vis[2 * prime[i]]) {
      tmp.push(2 * prime[i]);
      vis[2 * prime[i]] = 1;
    }
    if (tmp.size()) tmp.push(prime[i]);
    while (!tmp.empty()) {
      int a = tmp.front();
      tmp.pop();
      ans.push_back(make_pair(a, tmp.front()));
      tmp.pop();
    }
  }
  printf("%d\n", ans.size());
  for (auto it = ans.begin(); it != ans.end(); ++it)
    printf("%d %d\n", it->first, it->second);
  return 0;
}
