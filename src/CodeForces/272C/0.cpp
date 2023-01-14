#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
template <class T>
T chkmax(T &a, T b) {
  return a < b ? a = b : a;
}
const uint32_t N = 1e5 + 5;
int64_t h[N];
int main() {
  int n, m;
  cin >> n;
  _for(i, 1, n) cin >> h[i];
  cin >> m;
  int64_t mx = 0;
  _for(i, 1, m, x, y) {
    cin >> x >> y;
    cout << chkmax(mx, h[x]) << '\n';
    mx += y;
  }
  return 0;
}
