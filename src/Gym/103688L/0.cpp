#include <bits/stdc++.h>
using namespace std;
#define _run_return_void(expressions) \
  {                                   \
    expressions;                      \
    return;                           \
  }
const uint32_t OFFSET = 5;
const uint32_t N = 5e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
auto _rev = [](const string_view &s, int l) -> string {
  string _;
  for (int i = l - 1; ~i; --i) _.push_back(s[i]);
  for (int i = s.size() - 1; i >= l; --i) _.push_back(s[i]);
  return _;
};
namespace KMP {
int nxt[N];
int l;
bool kmp(const string_view &s, const string_view &t) {
  int i, j;
  int n = s.size(), m = t.size();
  for (nxt[0] = j = -1, i = 1; i < n; nxt[i++] = j) {
    while (~j && s[j + 1] != s[i]) j = nxt[j];
    if (s[j + 1] == s[i]) ++j;
  }
  for (j = -1, i = 0; i < m; ++i) {
    while (~j && s[j + 1] != t[i]) j = nxt[j];
    if (s[j + 1] == t[i]) ++j;
    if (j == n - 1) {
      if ((i - n + 1) % l == 0) return 1;
      j = nxt[j];
    }
  }
  return 0;
}
}  // namespace KMP
using KMP::kmp;
auto solve() -> void {
  string s, t;
  cin >> s >> t;
  int l1, l2;
  cin >> l1 >> l2;
  if (s == t) _run_return_void(cout << "yes\n");
  if (l1 == l2) _run_return_void(cout << (_rev(s, l1) == t ? "yes\n" : "no\n"));
  if (l1 > l2) swap(l1, l2);
  string _1 = _rev(s, l1), _2 = _rev(s, l2), _12 = _rev(_1, l2),
         _21 = _rev(_2, l1);
  t += t;
  KMP::l = gcd(l2 - l1, (int)s.size());
  cout << (kmp(_1, t) || kmp(_2, t) || kmp(_12, t) || kmp(_21, t) ? "yes\n" :
                                                                    "no\n");
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int _t;
  cin >> _t;
  while (_t--) solve();
  return 0;
}
