#include <bits/stdc++.h>
using i64 = int64_t;
#define for_(i, l, r, v...) for (i64 i = (l), i##e = (r), ##v; i <= i##e; ++i)
using namespace std;
class DsuBasic {
protected:
  std::vector<size_t> fa;

public:
  explicit DsuBasic(size_t size): fa(size) {
    std::iota(fa.begin(), fa.end(), 0);
  }
  size_t find(size_t x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
  bool merge(size_t x, size_t y) {
    size_t fx = find(x), fy = find(y);
    return fx == fy ? false : (fa[fx] = fy, true);
  }
};
void solve(int t_ = 0) {
  int n, s;
  cin >> n >> s;
  vector<int> d(n + 1);
  DsuBasic dsu(n + 1);
  int cnt_e = 0;
  for_(i, 2, n) {
    char ch;
    for_(j, 1, i - 1) {
      cin >> ch;
      if (ch & 1) continue;
      ++cnt_e;
      ++d[i];
      ++d[j];
      dsu.merge(i, j);
    }
  }
  int cnt_od = 0;
  for_(i, 1, n) cnt_od += d[i] & 1;
  if (cnt_od && (cnt_od != 2 || ~d[s] & 1)) {
    cout << "-1\n";
    return;
  }
  int cnt_c = 0;
  for_(i, 1, n) cnt_c += d[i] && i == dsu.find(i);
  cout << cnt_e + 2 * (cnt_c - !!d[s]) << '\n';
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
