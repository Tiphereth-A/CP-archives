#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int fa[N];
int find(int x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
bool merge(int x, int y) {
  return find(x) == find(y) ? false : fa[find(x)] = find(y), true;
}
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
auto solve([[maybe_unused]] int t_ = 0) -> void {
  int n;
  cin >> n;
  for_(i, 0, n * 2) fa[i] = i;
  string s;
  cin >> s;
  vector<vector<int>> bra(n + 2);
  int cnt = 0;
  for_(i, 0, n * 2 - 1) {
    if (s[i] == '(') {
      bra[++cnt].push_back(i);
    } else {
      bra[cnt + 1].clear();
      merge(i, bra[cnt].back());
      if (bra[cnt].size() > 1) merge(i, *(bra[cnt].end() - 2));
      --cnt;
    }
  }
  set<int> ss;
  for_(i, 0, n * 2 - 1) ss.insert(find(i));
  cout << ss.size() << '\n';
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int i_ = 0;
  int t_ = 0;
  std::cin >> t_;
  for (i_ = 0; i_ < t_; ++i_) solve(i_);
  return 0;
}
