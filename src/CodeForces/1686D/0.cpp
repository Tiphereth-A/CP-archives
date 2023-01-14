#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _all(a) (a).begin(), (a).end()
#define _run_return_void(expressions) \
  {                                   \
    expressions;                      \
    return;                           \
  }
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const uint32_t OFFSET = 5;
const uint32_t N = 2e5 + OFFSET, M = 2e5 + OFFSET, K = 21;
int base[N];
bool startswith_A[N];
int f[N];
auto solve() -> void {
  int a, b, ab, ba;
  cin >> a >> b >> ab >> ba;
  string s;
  cin >> s;
  int _a = count_if(_all(s), [](char ch) { return ch == 'A'; });
  if (_a != a + ab + ba) _run_return_void(cout << "NO\n");
  int cnt = 0;
  bool head = 1;
  char pre = s.front();
  for (size_t i = 1; i < s.size(); ++i) {
    char &now = s[i];
    if (pre == now) {
      head = 1;
      continue;
    }
    if (head) {
      startswith_A[++cnt] = pre == 'A';
      base[cnt] = 1;
      head = 0;
    }
    ++base[cnt];
    pre = now;
  }
  vector<pair<int, bool>> data_odd, data_even;
  data_even.reserve(cnt);
  data_odd.reserve(cnt);
  _for(i, 1, cnt)
    (base[i] & 1 ? data_odd : data_even).emplace_back(base[i], startswith_A[i]);
  sort(_all(data_odd));
  sort(_all(data_even));
  for (auto [i, b] : data_even) {
    if (!(i & 1) && b) {
      if (ab >= i / 2) {
        ab -= i / 2;
        continue;
      }
      if (ab) i -= ab * 2 + 2;
      if ((ba -= i / 2 - !ab) <= (ab = 0)) break;
      continue;
    }
    if (ba >= i / 2) {
      ba -= i / 2;
      continue;
    }
    if (ba) i -= ba * 2 + 2;
    if ((ab -= i / 2 - !ba) <= (ba = 0)) break;
  }
  if (ab > 0 || ba > 0)
    for (auto [i, b] : data_odd) {
      if (ba >= i / 2) {
        ba -= i / 2;
        continue;
      }
      if (ba) i -= ba * 2 + 1;
      if ((ab -= i / 2) <= (ba = 0)) break;
    }
  cout << (ab <= 0 && ba <= 0 ? "YES\n" : "NO\n");
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
