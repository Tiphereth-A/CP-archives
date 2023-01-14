#include <bits/stdc++.h>
int coin[110], money_state[25005];
int T, n;
int main() {
  scanf("%d ", &T);
  while (T--) {
    memset(money_state, 0, sizeof(money_state));
    int ans = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &coin[i]);
      money_state[coin[i]] = 2;
    }
    std::sort(coin + 1, coin + 1 + n);
    for (int i = 1; i <= coin[n]; ++i) {
      if (money_state[i]) {
        for (int j = 1; j <= n; ++j)
          if (i + coin[j] <= coin[n]) money_state[i + coin[j]] = 1;
          else break;
      }
    }
    for (int i = 1; i <= coin[n]; ++i)
      if (money_state[i] == 2) ++ans;
    printf("%d\n", ans);
  }
}
