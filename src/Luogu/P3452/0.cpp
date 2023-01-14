#include <bits/stdc++.h>
#define dbg(...) 42
using namespace std;
using u32 = uint32_t;
using i64 = int64_t;
template <class Tp>
using vec = vector<Tp>;
#define fors_(i, l, r, s, ...) \
  for (i64 i = (l), i##e = (r)__VA_OPT__(, ) __VA_ARGS__; i <= i##e; i += s)
#define for_(i, l, r, ...) fors_(i, l, r, 1 __VA_OPT__(, ) __VA_ARGS__)
#define rfors_(i, r, l, s, ...) \
  for (i64 i = (r), i##e = (l)__VA_OPT__(, ) __VA_ARGS__; i >= i##e; i -= s)
#define rfor_(i, r, l, ...) rfors_(i, r, l, 1 __VA_OPT__(, ) __VA_ARGS__)
void solve([[maybe_unused]] int t_ = 0) {
  u32 n, m;
  cin >> n >> m;
  vec<vec<u32>> g(n + 1);
  for_(i, 1, m, x, y) {
    cin >> x >> y;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  vec<bool> vis(n + 1);
  set<u32> ps;
  for_(i, 1, n) ps.insert(i);
  u32 sz = 0;
  vec<u32> cnt(n + 1);
  while (!ps.empty()) {
    ++sz;
    auto now = *ps.begin();
    queue<u32> q({now});
    ++cnt[sz];
    ps.erase(ps.begin());
    while (!q.empty()) {
      auto now = q.front();
      q.pop();
      for (auto i : g[now]) vis[i] = 1;
      for (auto it = ps.begin(); it != ps.end();)
        if (!vis[*it]) {
          ++cnt[sz];
          q.push(*it);
          it = ps.erase(it);
        } else ++it;
      for (auto i : g[now]) vis[i] = 0;
    }
  }
  ranges::sort(cnt, greater<>());
  cout << sz << '\n';
  rfor_(i, sz - 1, 0) cout << cnt[i] << " \n"[i == 0];
}
signed main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cerr << fixed << setprecision(6);
  int i_ = 0;
  dbg(i_), solve(i_);
  return 0;
}
