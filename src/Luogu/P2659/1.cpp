#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
namespace FastIO {
char buf[1 << 21], *p1 = buf, *p2 = buf;
int getc() {
  return p1 == p2 &&
             (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ?
           EOF :
           *p1++;
}
void read() {}
template <class T>
void read(T &x) {
  x = 0;
  char ch = getc();
  while (!isdigit(ch)) ch = getc();
  while (isdigit(ch)) { x = x * 10 + ch - '0', ch = getc(); }
}
template <typename T, typename... T2>
void read(T &x, T2 &...oth) {
  read(x);
  read(oth...);
}
}  // namespace FastIO
using FastIO::read;
bool operator<(const pii &lhs, const pii &rhs) { return lhs.first < rhs.first; }
int main() {
  int n;
  read(n);
  vector<pii> v;
  _for(i, 1, n, _) {
    read(_);
    v.emplace_back(_, i);
  }
  i64 ans = 0;
  vector<pii> s;
  s.emplace_back(0, 0);
  for (const auto &i : v) {
    if (s.size() == 1) {
      s.push_back(i);
      continue;
    }
    while (i < s.back()) {
      chkmax(ans,
             1ll * s.back().first * (i.second - (s.end() - 2)->second - 1));
      s.pop_back();
    }
    s.push_back(i);
  }
  for (auto it = s.begin() + 1; it != s.end(); ++it)
    chkmax(ans, 1ll * it->first * (n - (it - 1)->second));
  printf("%lld", ans);
  return 0;
}
