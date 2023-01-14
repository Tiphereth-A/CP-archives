#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;
const int MAXN = 111;
LL _n;
LL sum[MAXN], f[MAXN];
int vis[MAXN];
LL solve(LL n) {
  int po = 0;
  for (int i = 62; i >= 0; i--) {
    if (sum[i] == n) {
      LL tmp = 0;
      for (int j = i; j >= 0 && vis[j] == 0; j--) {
        tmp++;
        vis[j] = 1;
      }
      return tmp;
    } else if (sum[i] < n) {
      po = i;
      break;
    }
  }
  LL ret = 1;
  LL res = n - sum[po];
  if (res > f[po]) {
    for (int i = po; i >= 0 && vis[i] == 0; i--) {
      ret++;
      vis[i] = 1;
    }
    ret += solve(n - sum[po] - 1);
  } else {
    for (int i = po - 1; i >= 0 && vis[i] == 0; i--) {
      ret++;
      vis[i] = 1;
    }
    if (po >= 1) ret += solve(n - sum[po - 1] - 1);
    else ret += solve(n - 1);
  }
  return ret;
}
void get_table() {
  f[0] = 1;
  for (int i = 1; i < 63; i++) f[i] = f[i - 1] << 1;
  sum[0] = 1;
  for (int i = 1; i < 63; i++) sum[i] = sum[i - 1] + f[i];
}
void init() { memset(vis, 0, sizeof(vis)); }
int main() {
  get_table();
  while (scanf("%lld", &_n) == 1) {
    init();
    LL ans = solve(_n);
    printf("%lld\n", ans);
  }
  return 0;
}
