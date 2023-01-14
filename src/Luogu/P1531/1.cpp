#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
const int _N = 200005;
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define _rrep(i, l, r) for (int i = l; i >= r; --i)
int a[_N << 2], t[_N << 2];
int n, N = 1, m;
int max(int a, int b) {
  int m = (b - a) >> 31;
  return a & m | b & ~m;
}
void build() {
  _for(i, 1, n) t[N + i] = a[i];
  _rrep(i, N - 1, 1) t[i] = max(t[i << 1], t[i << 1 | 1]);
}
void modify(int x, int k) {
  for (int i = N + x; i; i >>= 1) t[i] = max(t[i], k);
}
int query(int x, int y) {
  int ans = 0;
  for (int s = N + x - 1, r = N + y + 1; s ^ r ^ 1; s >>= 1, r >>= 1) {
    if (~s & 1) ans = max(ans, t[s ^ 1]);
    if (r & 1) ans = max(ans, t[r ^ 1]);
  }
  return ans;
}
int main() {
  cin >> n >> m;
  while (N < n + 2) N <<= 1;
  _for(i, 1, n) cin >> a[i];
  build();
  char c;
  int x, y;
  while (m--) {
    cin >> c >> x >> y;
    if (c == 'Q') cout << query(x, y) << endl;
    else modify(x, y);
  }
  return 0;
}
