#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define N 100005
const int MOD = 99999997;
struct node {
  int num, id;
  bool operator<(const node &a) const { return this->num < a.num; }
} fst[N], snd[N];
int n, a[N], b[N];
i64 ans;
void merge(int l, int r) {
  if (l == r) return;
  int mid = (l + r) >> 1;
  merge(l, mid);
  merge(mid + 1, r);
  if (ans >= MOD) ans %= MOD;
  int i = l, j = mid + 1, k = l;
  while (i <= mid && j <= r) {
    if (a[i] > a[j]) {
      b[k++] = a[j++];
      ans += mid - i + 1;
      (ans > MOD) ? ans %= MOD : 0;
    } else b[k++] = a[i++];
  }
  while (i <= mid) b[k++] = a[i++];
  while (j <= r) b[k++] = a[j++];
  _for(i, l, r) a[i] = b[i];
}
int main() {
  scanf("%d", &n);
  _for(i, 1, n) {
    scanf("%lld", &fst[i].num);
    fst[i].id = i;
  }
  _for(i, 1, n) {
    scanf("%lld", &snd[i].num);
    snd[i].id = i;
  }
  std::sort(fst + 1, fst + n + 1);
  std::sort(snd + 1, snd + n + 1);
  _for(i, 1, n) a[fst[i].id] = snd[i].id;
  merge(1, n);
  printf("%d", ans % MOD);
  return 0;
}
