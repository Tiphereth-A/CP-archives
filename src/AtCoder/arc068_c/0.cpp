#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int N = 3e5 + 5;
pair<i64, i64> a[N];
i64 cnt[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  i64 n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) cin >> a[i].first >> a[i].second;
  for (int i = 1; i <= n; ++i) {
    auto &&[x, y] = a[i];
    ++cnt[x--];
    --cnt[y + 1];
    for (i64 l = 1, r; l <= x; l = r + 1) {
      r = min(x / (x / l), y / (y / l));
      if (x / l < y / l) {
        ++cnt[l];
        --cnt[r + 1];
      }
    }
  }
  i64 ans = 0;
  for (int i = 1; i <= m; ++i) cout << (ans += cnt[i]) << '\n';
  return 0;
}
