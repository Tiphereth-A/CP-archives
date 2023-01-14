#include <bits/extc++.h>
using namespace std;
using i64 = std::int64_t;
using vi = std::vector<int>;
using vi64 = std::vector<i64>;
#define for_(i, l, r, vars...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vars; i <= i##end; ++i)
#define foreach_cref_(i, container) for (const auto &i : container)
#define all_(a) (a).begin(), (a).end()
#define run_exec_(expressions, after_process) \
  {                                           \
    expressions;                              \
    after_process;                            \
  }
#define run_continue_(expressions) run_exec_(expressions, continue)
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
auto solve([[maybe_unused]] int t_) -> void {
  int n, m;
  cin >> n >> m;
  vi64 d;
  d.reserve(n + 1);
  d.push_back(0);
  for_(i, 1, n, x) {
    cin >> x;
    d.push_back(x);
  }
  for_(i, 1, n, x) {
    cin >> x;
    d[i] -= x;
  }
  partial_sum(all_(d), d.begin());
  set<int> s;
  queue<int> q;
  for_(i, 1, n) {
    if (!d[i]) run_continue_(q.push(i));
    s.insert(i);
  }
  vector<vi> g(n + 1);
  for_(i, 1, m, l, r) {
    cin >> l >> r;
    g[l - 1].push_back(r);
    g[r].push_back(l - 1);
  }
  int cnt = 0;
  while (!q.empty()) {
    ++cnt;
    auto &&now = q.front();
    foreach_cref_(i, g[now]) {
      if (d[i]) continue;
      auto &&[l, r] = minmax(now, i);
      for (auto it = s.lower_bound(l); it != s.end() && *it <= r;
           it = s.erase(it)) {
        q.push(*it);
        d[*it] = 0;
      }
    }
    q.pop();
  }
  cout << (cnt == n ? "YES\n" : "NO\n");
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int i_ = 0;
  int t_;
  std::cin >> t_;
  for (i_ = 1; i_ <= t_; ++i_) solve(i_);
  return 0;
}
