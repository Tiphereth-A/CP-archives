#include <bits/stdc++.h>
using ll = long long;
using namespace std;
const int N = 300010;
int n, m, a[N], t[N];
void insert(int x) {
  for (; x <= n; x += x & (-x)) t[x]++;
}
int query(int x) {
  int y = 0;
  for (; x; x -= x & (-x)) y += t[x];
  return y;
}
void solve(int t_ = 0) {
  cin >> n >> m;
  ll ans = 0;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    ans += i - 1 - query(a[i]);
    insert(a[i]);
  }
  cout << ans << "\n";
  string s;
  cin >> s;
  int now = 1, flag = 1;
  for (int i = 0; i < m; ++i) {
    if (s[i] == 'S') {
      ans = ans + n + 1 - 2ll * a[now];
      if (flag == 1) now = now % n + 1;
      else {
        now--;
        if (!now) now = n;
      }
    } else {
      ans = (ll)n * (n - 1) / 2 - ans;
      flag = -flag;
      if (flag == 1) now = now % n + 1;
      else {
        now--;
        if (!now) now = n;
      }
    }
    cout << ans % 10;
  }
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
