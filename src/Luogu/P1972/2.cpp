#include <algorithm>
#include <iostream>
int n, m, a[1000010], ans[1000010];
int pre[1000010], lst[1000010];
struct ope {
  int type, x, y, id;
  ope(int type = 0, int x = 0, int y = 0, int id = 0) {
    this->type = type, this->x = x, this->y = y, this->id = id;
  }
  bool operator<(const ope &rhs) const {
    if (x == rhs.x) return type < rhs.type;
    return x < rhs.x;
  }
};
ope op[2500010];
int tot;
int sum[1000010];
int lowbit(int x) { return x & (-x); }
void add(int x, int k) {
  x++;
  while (x <= n) {
    sum[x] = sum[x] + k;
    x = x + lowbit(x);
  }
}
int getsum(int x) {
  x++;
  int ret = 0;
  while (x > 0) {
    ret = ret + sum[x];
    x = x - lowbit(x);
  }
  return ret;
}
using std::cin;
using std::cout;
int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    pre[i] = lst[a[i]], lst[a[i]] = i;
    op[++tot] = ope{0, i, pre[i], i};
  }
  cin >> m;
  for (int i = 1, l, r; i <= m; i++) {
    cin >> l >> r;
    op[++tot] = ope{1, r, l - 1, i};
    op[++tot] = ope{2, l - 1, l - 1, i};
  }
  std::sort(op + 1, op + tot + 1);
  for (int i = 1; i <= tot; i++) {
    if (op[i].type == 0) add(op[i].y, 1);
    else if (op[i].type == 1) ans[op[i].id] += getsum(op[i].y);
    else ans[op[i].id] -= getsum(op[i].y);
  }
  for (int i = 1; i <= m; i++) cout << ans[i] << '\n';
  return 0;
}
