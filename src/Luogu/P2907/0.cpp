#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
ll k, n;
ll dfs(int v) {
  if (v <= k) return 1;
  if ((v - k) % 2 == 0) return (dfs((v - k) / 2) + dfs((v + k) / 2));
  else return 1;
}
int main() {
  scanf("%lld%lld", &n, &k);
  printf("%lld", dfs(n));
  return 0;
}
