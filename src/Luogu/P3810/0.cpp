#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
namespace BIT {
int tr[N], k;
#define lowbit(i) ((i) & -(i))
void insert(int pos, int val) {
  for (; pos <= k; pos += lowbit(pos)) tr[pos] += val;
}
int query(int pos) {
  int ret = 0;
  for (; pos; pos -= lowbit(pos)) ret += tr[pos];
  return ret;
}
}  // namespace BIT
using namespace BIT;
struct Node {
  int a, b, c, cnt, ans;
  bool operator!=(const Node &rhs) const {
    return a != rhs.a || b != rhs.b || c != rhs.c;
  }
} num[N], tmp[N];
int len_num;
auto cmp_bc = [](const Node &lhs, const Node &rhs) {
  return lhs.b == rhs.b ? lhs.c < rhs.c : lhs.b < rhs.b;
};
auto cmp_abc = [](const Node &lhs, const Node &rhs) {
  return lhs.a == rhs.a ? cmp_bc(lhs, rhs) : lhs.a < rhs.a;
};
void divide(int l, int r) {
  if (l == r) return;
  int mid = (l + r) / 2;
  divide(l, mid);
  divide(mid + 1, r);
  stable_sort(num + l, num + mid + 1, cmp_bc);
  stable_sort(num + mid + 1, num + r + 1, cmp_bc);
  int i = l;
  for (int j = mid + 1; j <= r; ++j) {
    while (num[i].b <= num[j].b && i <= mid) {
      insert(num[i].c, num[i].cnt);
      ++i;
    }
    num[j].ans += query(num[j].c);
  }
  for (int _ = l; _ < i; ++_) insert(num[_].c, -num[_].cnt);
}
int stat[N];
int main() {
  int n;
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i) scanf("%d%d%d", &tmp[i].a, &tmp[i].b, &tmp[i].c);
  sort(tmp + 1, tmp + n + 1, cmp_abc);
  for (int i = 1, cnt = 1; i <= n; ++i, ++cnt)
    if (tmp[i] != tmp[i + 1]) {
      num[++len_num] = {tmp[i].a, tmp[i].b, tmp[i].c, cnt, 0};
      cnt = 0;
    }
  divide(1, len_num);
  for (int i = 1; i <= len_num; ++i)
    stat[num[i].ans + num[i].cnt] += num[i].cnt;
  for (int i = 1; i <= n; ++i) printf("%d\n", stat[i]);
  return 0;
}
