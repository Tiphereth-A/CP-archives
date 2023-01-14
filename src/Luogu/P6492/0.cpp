#include <bits/stdc++.h>
using namespace std;
#define _lch ((p) << 1)
#define _rch ((p) << 1 | 1)
#define _mid(l, r) ((l) + (((r) - (l)) >> 1))
const int N = 2e5 + 5;
int n, m;
struct node_sgt {
  int l, r, m;
} tr[N << 2];
bool a[N];
void push_up(int p, int l, int r, int mid) {
  if ((tr[p].l = tr[_lch].l) == mid - l + 1 && (a[mid] ^ a[mid + 1]))
    tr[p].l += tr[_rch].l;
  if ((tr[p].r = tr[_rch].r) == r - mid && (a[mid] ^ a[mid + 1]))
    tr[p].r += tr[_lch].r;
  tr[p].m = max(tr[_lch].m, tr[_rch].m);
  if (a[mid] ^ a[mid + 1]) tr[p].m = max(tr[p].m, tr[_lch].r + tr[_rch].l);
}
void init(int p = 1, int l = 1, int r = n) {
  if (l == r) {
    tr[p] = {1, 1, 1};
    return;
  }
  int mid = _mid(l, r);
  init(_lch, l, mid);
  init(_rch, mid + 1, r);
  push_up(p, l, r, mid);
}
void modify(int pos, int p = 1, int l = 1, int r = n) {
  if (l == r) {
    a[l] = !a[l];
    return;
  }
  int mid = _mid(l, r);
  if (mid >= pos) modify(pos, _lch, l, mid);
  else modify(pos, _rch, mid + 1, r);
  push_up(p, l, r, mid);
}
int main() {
  cin >> n >> m;
  init();
  for (int i = 1, _; i <= m; ++i) {
    cin >> _;
    modify(_);
    cout << max(tr[1].m, max(tr[1].r, tr[1].l)) << endl;
  }
  return 0;
}
