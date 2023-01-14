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
  int n, m;
  cin >> n >> m;
  vc<int> a(m + 2, 0);
  a.front() = a.back() = -1;
  vc<int> l(m + 1), r(m + 1);
  auto f = [&](int n) -> i64 {
    iota(l.begin(), l.end(), 0);
    for_(i, 1, n)
      while (a[l[i] - 1] >= a[i]) l[i] = l[l[i] - 1];
    iota(r.begin(), r.end(), 0);
    rfor_(i, n, 1)
      while (a[r[i] + 1] >= a[i]) r[i] = r[r[i] + 1];
    i64 ans = 0;
    for_(i, 1, n) ans = max(ans, 1ll * (r[i] - l[i] + 1) * a[i]);
    return ans;
  };
  i64 ans = 0;
  for_(i, 1, n) {
    char ch;
    for_(i, 1, m) {
      cin >> ch;
      a[i] = ch == 'F' ? a[i] + 1 : 0;
    }
    ans = max(ans, f(m));
  }
  cout << ans * 3;
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
