#include <bits/stdc++.h>
using ll = long long;
using i64 = ll;
template <class Tp>
using vc = std::vector<Tp>;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
#define rfor_(i, r, l, v...) for (ll i = (r), i##e = (l), ##v; i >= i##e; --i)
template <class Tp>
Tp dec(Tp &i) {
  return --i;
}
template <class Tp>
Tp inc(Tp &i) {
  return ++i;
}
using namespace std;
void solve(int t_ = 0) {
  int n;
  bool f = 0;
  while (cin >> n) {
    if (f) cout << '\n';
    f = 1;
    vc<i64> a(n + 2, -1), p(n + 2);
    for_(i, 1, n) cin >> a[i];
    partial_sum(a.begin() + 1, a.end() - 1, p.begin() + 1);
    vc<int> l(n + 1), r(n + 1);
    iota(l.begin(), l.end(), 0);
    for_(i, 1, n)
      while (a[l[i] - 1] >= a[i]) l[i] = l[l[i] - 1];
    iota(r.begin(), r.end(), 0);
    rfor_(i, n, 1)
      while (a[r[i] + 1] >= a[i]) r[i] = r[r[i] + 1];
    i64 ans = 0;
    int ansl = 1, ansr = 1;
    for_(i, 1, n) {
      i64 _ = (p[r[i]] - p[l[i] - 1]) * a[i];
      if (_ > ans ||
          (_ == ans && (ansr - ansl > r[i] - l[i] ||
                        ansr - ansl == r[i] - l[i] && ansl > l[i]))) {
        ans = _;
        ansl = l[i];
        ansr = r[i];
      }
    }
    cout << ans << '\n' << ansl << ' ' << ansr << '\n';
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
