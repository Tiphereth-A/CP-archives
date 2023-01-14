#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int bottle[N];
int a, b;
int main() {
  auto judge = [](int dis) -> bool {
    int tot = 1;
    for (int now_bottle = bottle[1], i = 2; i <= a; ++i)
      if (bottle[i] - now_bottle >= dis) {
        now_bottle = bottle[i];
        ++tot;
      }
    return tot >= b;
  };
  cin >> a >> b;
  if (b == 1) {
    cout << "0";
    return 0;
  }
  for (int i = 1; i <= a; ++i) cin >> bottle[i];
  sort(bottle + 1, bottle + a + 1);
  int l = 0, r = bottle[a] - bottle[1], mid = 0, ans = -1;
  while (l <= r)
    if (judge(mid = ((r - l) >> 1) + l)) {
      l = mid + 1;
      ans = std::max(ans, mid);
    } else r = mid - 1;
  cout << ans;
}
