#include <bits/stdc++.h>
using namespace std;
struct DsuBasic {
  vector<int> fa;
  explicit DsuBasic(int size): fa(size) { iota(fa.begin(), fa.end(), 0); }
  int find(int x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
  bool merge(int x, int y) {
    int fx = find(x), fy = find(y);
    return fx == fy ? false : (fa[fx] = fy, true);
  }
};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t_ = 0;
  cin >> t_;
  while (t_--) {
    int n, s;
    cin >> n >> s;
    vector<int> d(n + 1);
    DsuBasic dsu(n + 1);
    int cnt_e = 0;
    for (int i = 2; i <= n; ++i) {
      char ch;
      for (int j = 1; j < i; ++j) {
        cin >> ch;
        if (ch == '1') continue;
        ++cnt_e;
        ++d[i];
        ++d[j];
        dsu.merge(i, j);
      }
    }
    int cnt_od = 0;
    for (int i = 1; i <= n; ++i) cnt_od += d[i] % 2;
    if (cnt_od && (cnt_od != 2 || d[s] % 2 == 0)) {
      cout << "-1\n";
      continue;
    }
    int cnt_c = 0;
    for (int i = 1; i <= n; ++i)
      if (d[i] && i == dsu.find(i)) ++cnt_c;
    cout << cnt_e + 2 * (cnt_c - (d[s] ? 1 : 0)) << '\n';
  }
  return 0;
}
