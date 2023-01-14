#include <algorithm>
#include <iostream>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
#define _set_nul_n(a, n) memset(a, 0, sizeof(a[0]) * (n))
const uint32_t N = 1e5 + 5;
struct ptree {
  int val, l, r;
} tree[N * 24];
int root[N], node_cnt;
#define PRE tree[pre]
#define PREL tree[L]
#define PRER tree[R]
#define NOW tree[now]
void modify(int pre, int l, int r, int &now, int pos) {
  tree[now = ++node_cnt] = {PRE.val + 1, PRE.l, PRE.r};
  if (l == r) return;
  int mid = _mid(l, r);
  if (pos <= mid) modify(PRE.l, l, mid, NOW.l, pos);
  else modify(PRE.r, mid + 1, r, NOW.r, pos);
}
int query(int L, int R, int l, int r, int k) {
  if (l == r) return k >= l ? PRER.val - PREL.val : 0;
  int mid = _mid(l, r);
  if (mid > k) return query(PREL.l, PRER.l, l, mid, k);
  int tmp = tree[PRER.l].val - tree[PREL.l].val;
  if (mid == k) return tmp;
  else return tmp + query(PREL.r, PRER.r, mid + 1, r, k);
}
int a[N], b[N], b_len;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int _t;
  cin >> _t;
  while (_t--) {
    int n, q;
    cin >> n >> q;
    node_cnt = 0;
    _set_nul_n(root, n + 1);
    _for(i, 1, n) cin >> a[i];
    _for(i, 1, n) b[i] = a[i];
    sort(b + 1, b + n + 1);
    b_len = unique(b + 1, b + n + 1) - b - 1;
    _for(i, 1, n)
      modify(root[i - 1],
             1,
             b_len,
             root[i],
             lower_bound(b + 1, b + b_len + 1, a[i]) - b);
    _for(i, 1, q, l, r, h) {
      cin >> l >> r >> h;
      cout << query(root[l - 1],
                    root[r],
                    1,
                    b_len,
                    upper_bound(b + 1, b + b_len + 1, h) - b - 1)
           << " \n"[i == q];
    }
  }
}
