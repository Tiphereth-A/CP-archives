#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (int i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _rfor(i, r, l, vals...) \
  for (int i = (r), i##end = (l), ##vals; i >= i##end; --i)
const uint32_t OFFSET = 5;
const uint32_t N = 2e5 + OFFSET;
int a[N], pre[N], suf[N];
bool dc(int L, int R) {
  if (L == R) return 1;
  int k = -1;
  for (int i = 0; L + i <= R - i; ++i) {
    if (pre[L + i] < L && suf[L + i] > R) {
      k = L + i;
      break;
    }
    if (pre[R - i] < L && suf[R - i] > R) {
      k = R - i;
      break;
    }
  }
  if (k == -1) return 0;
  bool f1 = 1, f2 = 1;
  if (L < k) f1 = dc(L, k - 1);
  if (k < R) f2 = dc(k + 1, R);
  return f1 & f2;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int _t;
  cin >> _t;
  while (_t--) {
    int n;
    cin >> n;
    {
      map<int, int> m;
      _for(i, 1, n) cin >> a[i];
      _for(i, 1, n) {
        pre[i] = m.count(a[i]) ? m[a[i]] : -1;
        m[a[i]] = i;
      }
    }
    {
      map<int, int> m;
      _rfor(i, n, 1) {
        suf[i] = m.count(a[i]) ? m[a[i]] : n + 1;
        m[a[i]] = i;
      }
    }
    cout << (dc(1, n) ? "non-boring\n" : "boring\n");
  }
  return 0;
}
