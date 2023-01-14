#include <algorithm>
#include <cstdio>
const int N = 2e5 + 10;
struct node {
  i64 x;
  int type;
  bool operator<(const node &oth) const {
    return x == oth.x ? type < oth.type : x < oth.x;
  }
} a[N];
i64 b[N];
i64 max(i64 a, i64 b) { return a > b ? a : b; }
int main() {
  int kase;
  scanf("%d", &kase);
  while (kase--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
      scanf("%lld%lld", &a[2 * i - 1].x, &a[2 * i].x);
      a[2 * i - 1].type = 1;
      a[2 * i].type = -1;
    }
    n <<= 1;
    std::sort(a + 1, a + n + 1);
    i64 sum = 0, ans_num = 0;
    int r = 0;
    for (int i = 1; i <= n; ++i) {
      sum += a[i].type;
      if (sum > ans_num) b[++r] = a[i].x;
      ans_num = max(ans_num, sum);
    }
    sum = 0;
    i64 ans_time = 0, e_max = 0;
    for (int i = n; i >= 1; --i) {
      sum -= a[i].type;
      if (sum > e_max) {
        ans_time += a[i].x - b[r];
        r--;
      }
      e_max = max(e_max, sum);
    }
    printf("%lld %lld\n", ans_num, ans_time);
  }
}
