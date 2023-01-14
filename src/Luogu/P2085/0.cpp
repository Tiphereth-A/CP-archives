#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
using tp = tuple<i64, i64, i64>;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<function<i64(i64)>> vfunc;
  vfunc.reserve(n);
  for (int i = 0, a, b, c; i < n; ++i) {
    cin >> a >> b >> c;
    vfunc.emplace_back([a, b, c](i64 x) { return a * x * x + b * x + c; });
  }
  priority_queue<tp, vector<tp>, greater<tp>> q;
  for (int i = 0; i < n; ++i) q.emplace(vfunc[i](1), i, 1);
  for (int i = 0; i < m; ++i) {
    auto [res, idx, x] = q.top();
    cout << res << " \n"[i == m - 1];
    q.pop();
    q.emplace(vfunc[idx](x + 1), idx, x + 1);
  }
  return 0;
}
