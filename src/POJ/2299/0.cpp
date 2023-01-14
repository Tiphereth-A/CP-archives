#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 5e5 + 50;
i64 a[N], b[N], c[N];
i64 lowbit(i64 x) { return x & (-x); }
i64 query(i64 x) {
  i64 ret = 0;
  while (x > 0) {
    ret += c[x];
    x -= lowbit(x);
  }
  return ret;
}
void update(i64 x) {
  while (x <= N - 50) {
    ++c[x];
    x += lowbit(x);
  }
}
int main() {
  i64 n;
  while (~scanf("%lld", &n) && n) {
    memset(c, 0, sizeof(c));
    for (int i = 1; i <= n; ++i) {
      scanf("%lld", &a[i]);
      b[i] = a[i];
    }
    sort(b + 1, b + n + 1);
    i64 len = unique(b + 1, b + n + 1) - b, ans = 0;
    for (int i = 1; i <= n; ++i) {
      i64 x = lower_bound(b + 1, b + len + 1, a[i]) - b;
      ans += i - query(x - 1) - 1;
      update(x);
    }
    printf("%lld\n", ans);
  }
  return 0;
}
