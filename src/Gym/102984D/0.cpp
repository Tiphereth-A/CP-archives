#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
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
const uint32_t N = 5e5 + OFFSET;
int a[N];
int block_id[N], block_end[N];
i64 sum_f[N];
auto _ = [](i64 len) -> i64 { return len * (len + 1) / 2; };
i64 query(int l, int r) {
  if (l > r) swap(l, r);
  if (block_id[r] == block_id[l]) return _(r - l + 1);
  return _(r - block_end[block_id[r] - 1]) + _(block_end[block_id[l]] - l + 1) +
         sum_f[block_id[r] - 1] - sum_f[block_id[l]];
}
i64 f(int l, int r, int x) { return max(query(l, x), query(x, r)); }
i64 tri(int l, int r) {
  int mid1, mid2;
  i64 f1, f2;
  i64 ans = INT64_MAX;
  int _l = l, _r = r;
  while (_r - _l > 10) {
    f1 = f(l, r, mid1 = _l + (_r - _l) / 3);
    f2 = f(l, r, mid2 = _r - (_r - _l) / 3);
    ans = min({ans, f1, f2});
    if (f1 > f2) _l = mid1;
    else _r = mid2;
  }
  _for(i, _l, _r) chkmin(ans, f(l, r, i));
  return ans;
}
auto solve() -> void {
  int n, m;
  cin >> n >> m;
  _for(i, 1, n) cin >> a[i];
  int cnt = 1;
  _for(i, 1, n) {
    if (a[i] < a[i - 1]) ++cnt;
    block_end[block_id[i] = cnt] = i;
  }
  _for(i, 1, cnt) sum_f[i] = sum_f[i - 1] + _(block_end[i] - block_end[i - 1]);
  _for(i, 1, m, l, r) {
    cin >> l >> r;
    cout << tri(l, r) << '\n';
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  solve();
  return 0;
}
