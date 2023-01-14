#include <bits/stdc++.h>
using ll = long long;
#define for_(i, l, r, v...) for (ll i = (l), i##e = (r), ##v; i <= i##e; ++i)
#define Rep for_
template <class Tp>
Tp dec(Tp &i) {
  return --i;
}
template <class Tp>
Tp inc(Tp &i) {
  return ++i;
}
using namespace std;
namespace KMP {
const int N = 1e6 + 5;
int nxt[N];
void kmp(string const &a) {
  int n = a.size();
  int i, j;
  for (nxt[0] = j = -1, i = 1; i < n; nxt[i++] = j) {
    while (~j && a[j + 1] != a[i]) j = nxt[j];
    if (a[j + 1] == a[i]) ++j;
  }
}
}  // namespace KMP
using KMP::kmp, KMP::nxt;
void solve(int t_ = 0) {
  string s;
  cin >> s;
  int len = s.size();
  kmp(s);
  vector<int> ans(len);
  int j = len - 1;
  while (~nxt[j]) {
    ans[nxt[j]]++;
    j = nxt[j];
  }
  Rep(i, 1, len - 1) ans[i] += ans[i - 1];
  cin >> t_;
  while (t_--) {
    int x;
    cin >> x;
    int tem = min(x - 1, (int)len - x);
    cout << (tem <= 0 ? 0 : ans[tem - 1]) << '\n';
  }
}
signed main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr << std::fixed << std::setprecision(6);
  int i_ = 0;
  solve(i_);
  return 0;
}
