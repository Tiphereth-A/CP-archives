#include <bits/stdc++.h>
using namespace std;
array<int, 51> a;
int maxa, mina = 114514, sum, l, __;
bool dfs(int ub = maxa, int now = 0, int cab = 0) {
  if (now >= __) return 1;
  if (cab == l) return dfs(maxa, now + 1);
  for (int i = ub; i >= mina; --i)
    if (a[i] && cab + i <= l) {
      --a[i];
      if (dfs(i, now, cab + i)) return 1;
      ++a[i];
      if (cab == 0 || cab + i == l) return 0;
    }
  return 0;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  for (int i = 1, x; i <= n; ++i) {
    cin >> x;
    ++a[x];
    maxa = max(maxa, x);
    mina = min(mina, x);
    sum += x;
  }
  for (l = maxa; l <= sum / 2; ++l) {
    if (sum % l) continue;
    __ = sum / l;
    if (dfs()) {
      cout << l;
      return 0;
    }
  }
  cout << sum;
  return 0;
}
