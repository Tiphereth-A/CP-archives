#include <bits/stdc++.h>
using std::cin;
using std::cout;
const int N = 1e5 + 5;
int f1[N], f2[N], cnt1 = 1, cnt2 = 1;
int main() {
  int tmp;
  scanf("%d", &tmp);
  f1[1] = f2[1] = tmp;
  while (~scanf("%d", &tmp)) {
    if (tmp <= f1[cnt1]) f1[++cnt1] = tmp;
    else
      f1[std::upper_bound(f1 + 1, f1 + cnt1 + 1, tmp, std::greater<int>()) -
         f1] = tmp;
    if (tmp > f2[cnt2]) f2[++cnt2] = tmp;
    else f2[std::lower_bound(f2 + 1, f2 + cnt2 + 1, tmp) - f2] = tmp;
  }
  printf("%d\n%d", cnt1, cnt2);
  return 0;
}
