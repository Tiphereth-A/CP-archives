#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
#define _rfor(i, r, l, vals...) \
  for (make_signed_t<decltype(r - l)> i = (r), ##vals; i >= (l); --i)
const int N = 3e5 + 5;
struct Node {
  i64 k, t, idx;
} q[N];
i64 a[N], ans[N];
i64 block[N * 2];
int main() {
  int n, m;
  cin >> n;
  _for(i, 1, n) cin >> a[i];
  int block_len = sqrt(n);
  cin >> m;
  i64 cnt = 0;
  _for(i, 1ll, m, t, k) {
    cin >> t >> k;
    if (k > block_len) {
      for (i64 j = t; j <= n; j += k) ans[i] += a[j];
      continue;
    }
    q[++cnt] = {k, t, i};
  }
  sort(q + 1, q + cnt + 1, [](const Node &lhs, const Node &rhs) {
    return lhs.k < rhs.k;
  });
  _for(i, 1ll, cnt, now_k) {
    now_k = q[i].k;
    memset(block, 0, sizeof(block));
    _rfor(j, n, 1) block[j] = block[j + now_k] + a[j];
    while (q[i].k == now_k) {
      ans[q[i].idx] = block[q[i].t];
      ++i;
    }
    --i;
  }
  _for(i, 1, m) cout << ans[i] << '\n';
  return 0;
}
