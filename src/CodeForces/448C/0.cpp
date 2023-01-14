#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
const int N = 1e5 + 5;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
int a[N];
i64 calc(i64 l, i64 r) {
  if (l < 1 || r < 1 || l > r) return 0;
  if (l == r) return min(a[l], 1);
  i64 mina = a[l], idx = l;
  _for(i, l + 1, r)
    if (a[i] < mina) mina = a[idx = i];
  _for(i, l, r) a[i] -= mina;
  i64 resl = calc(l, idx - 1), resr = calc(idx + 1, r);
  return min(r - l + 1, resl + resr + mina);
}
int main() {
  i64 n;
  cin >> n;
  _for(i, 1, n) scanf("%d", a + i);
  printf("%lld", min(n, calc(1, n)));
  return 0;
}
