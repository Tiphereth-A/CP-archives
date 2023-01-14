#include <bits/stdc++.h>
using namespace std;
const int OFFSET = 5, N = 1e5 + OFFSET;
const int MOD = 1e9 + 7;
int f[N] = {1, 1};
bool is_broken[N];
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1, _; i <= m; ++i) {
    scanf("%d", &_);
    is_broken[_] = 1;
  }
  if (is_broken[n]) {
    puts("0");
    return 0;
  }
  if (is_broken[1]) f[1] = 0;
  for (int i = 2; i <= n; ++i) {
    if (is_broken[i]) continue;
    f[i] = (f[i - 1] + f[i - 2]) % MOD;
  }
  printf("%d\n", f[n]);
  return 0;
}
