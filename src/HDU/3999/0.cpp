#include <cstdio>
const int N = 1e5 + 5;
struct Tree {
  int val, id;
  int l, r;
} bst[N];
int cnt_bst;
void insert(int val, int fa) {
  if (val > bst[fa].val) {
    if (bst[fa].r) insert(val, bst[fa].r);
    else bst[bst[fa].r = ++cnt_bst] = {val, cnt_bst, 0, 0};
  } else {
    if (bst[fa].l) insert(val, bst[fa].l);
    else bst[bst[fa].l = ++cnt_bst] = {val, cnt_bst, 0, 0};
  }
}
int ans[N], cnt_ans;
void pre(int idx) {
  if (!idx) return;
  ans[++cnt_ans] = bst[idx].val;
  pre(bst[idx].l);
  pre(bst[idx].r);
}
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1, _; i <= n; ++i) {
    scanf("%d", &_);
    insert(_, 0);
  }
  pre(1);
  printf("%d", ans[1]);
  for (int i = 2; i <= cnt_ans; ++i) printf(" %d", ans[i]);
  puts("");
}
