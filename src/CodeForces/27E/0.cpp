#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 70;
ll pr, mx, bgn, end = 1e18;
int prime[N];
bool chk[N];
int tot, n;
void initprime() {
  _for(i, 2, 50) {
    if (!chk[i]) prime[++tot] = i;
    _for(j, 1, tot) {
      if (i * prime[j] > 50) break;
      chk[i * prime[j]] = 1;
      if (i % prime[j] == 0) break;
    }
  }
  return;
}
void dfs(ll cur, int cnt, int dep, int up) {
  if (dep > tot) return;
  if ((cnt > mx || cnt == mx && pr > cur) && cnt == n) {
    pr = cur;
    mx = cnt;
  }
  _for(i, 1, up) {
    if (end / cur < prime[dep]) return;
    if ((bgn - 1) / cur == end / cur) return;
    cur *= prime[dep];
    dfs(cur, cnt * (i + 1), dep + 1, i);
  }
}
int main() {
  initprime();
  scanf("%d", &n);
  dfs(1, 1, 1, 64);
  printf("%lld", pr);
  return 0;
}
