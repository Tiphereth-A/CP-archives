#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const uint32_t OFFSET = 5;
const uint32_t N = 2e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
int a[N];
bool vis[N];
vector<tuple<int, int, int>> op;
void solve() {
  int n, q;
  cin >> n;
  _for(i, 1, n) cin >> a[i];
  cin >> q;
  op.reserve(q);
  int now_max = 0;
  _for(i, 1, q, x, y, z) {
    cin >> x >> y;
    if (x == 1) cin >> z;
    op.emplace_back(x, y, z);
  }
  for (auto it = op.rbegin(); it != op.rend(); ++it)
    if (get<0>(*it) == 1) {
      if (!vis[get<1>(*it)]) {
        vis[get<1>(*it)] = 1;
        a[get<1>(*it)] = max(now_max, get<2>(*it));
      }
    } else chkmax(now_max, get<1>(*it));
  _for(i, 1, n) cout << (vis[i] ? a[i] : max(now_max, a[i])) << " \n"[i == n];
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
