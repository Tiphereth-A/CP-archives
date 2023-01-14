#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5, BLOCK_N = 4e2 + 5;
i64 n, a[N];
i64 block_len, block_cnt;
i64 blocks[BLOCK_N], block_id[N];
i64 block_l(i64 b_id) { return max(1ll, b_id * block_len); }
i64 block_r(i64 b_id) { return min(n, (b_id + 1) * block_len - 1); }
void init() {
  block_len = sqrt(n);
  block_cnt = sqrt(n) + (n != block_len * block_len);
  for (int i = 0; i < block_cnt; ++i) blocks[i] = INT_MAX;
  for (int i = 1; i <= n; ++i)
    blocks[block_id[i] = i / block_len] = min(a[i], blocks[i / block_len]);
}
void modify(i64 pos, i64 num) {
  if (a[pos] != blocks[block_id[pos]]) {
    blocks[block_id[pos]] = min(a[pos] = num, blocks[block_id[pos]]);
    return;
  }
  blocks[block_id[pos]] = a[pos] = num;
  for (int i = block_l(block_id[pos]); i <= block_r(block_id[pos]); ++i)
    blocks[block_id[pos]] = min(a[i], blocks[block_id[pos]]);
}
i64 query(i64 pos) {
  i64 l_bid = block_id[pos], r_bid = block_id[pos];
  while (l_bid && blocks[l_bid] >= a[pos]) --l_bid;
  if (l_bid < block_id[pos] && blocks[l_bid] < a[pos]) ++l_bid;
  while (r_bid < n && blocks[r_bid] >= a[pos]) ++r_bid;
  if (r_bid > block_id[pos] && blocks[r_bid] < a[pos]) --r_bid;
  i64 l = block_l(l_bid), r = block_r(r_bid);
  if (l_bid == block_id[pos]) l = pos;
  while (l && a[l] >= a[pos]) --l;
  if (a[l] < a[pos]) ++l;
  if (r_bid == block_id[pos]) r = pos;
  while (r <= n && a[r] >= a[pos]) ++r;
  if (a[r] < a[pos]) --r;
  i64 l_len = pos - l + 1, r_len = r - pos + 1;
  return l_len * r_len;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int m;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  init();
  i64 op, x, y;
  for (int i = 1; i <= m; ++i) {
    cin >> op >> x;
    if (op == 1) {
      cin >> y;
      modify(x, y);
    } else {
      cout << query(x) << endl;
    }
  }
  return 0;
}
