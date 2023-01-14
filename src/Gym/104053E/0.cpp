#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
struct Node {
  int x, id;
  Node(int x = 0, int id = 0): x(x), id(id) {}
};
struct Fenwick {
  vector<i64> v;
  explicit Fenwick(i64 x): v(x) {}
  static constexpr i64 lowbit(i64 x) { return x & (-x); }
  void update(i64 pos, i64 x) {
    for (i64 i = pos; i < v.size(); i += lowbit(i)) v[i] += x;
  }
  i64 sum(i64 pos) const {
    i64 ans = 0;
    for (i64 i = pos; i; i -= lowbit(i)) ans += v[i];
    return ans;
  }
};
const int N = 500000 + 7;
i64 A[N], B[N], C[N], Ans[N];
void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) cin >> A[i], B[i] = A[i];
  sort(B + 1, B + 1 + n);
  int Sz = unique(B + 1, B + 1 + n) - B - 1;
  for (int i = 1; i <= n; ++i) C[i] = lower_bound(B + 1, B + 1 + Sz, A[i]) - B;
  Fenwick T1(n + 1), T2(n + 1);
  for (int i = 1; i <= n; ++i) {
    Ans[i] += T1.sum(C[i]);
    Ans[i] += T1.sum(C[i]) * A[i] - T2.sum(C[i]);
    T1.update(C[i], 1);
    T2.update(C[i], A[i]);
  }
  Fenwick T3(n + 1), T4(n + 1);
  for (int i = n; i >= 1; --i) {
    Ans[i] += T3.sum(C[i]) * A[i] - T4.sum(C[i]);
    T3.update(C[i], 1);
    T4.update(C[i], A[i]);
  }
  for (int i = 1; i <= n; ++i) cout << (Ans[i] <= m - 2 ? Ans[i] : -1) << '\n';
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int i_ = 0;
  int t_ = 0;
  cin >> t_;
  solve();
  return 0;
}
