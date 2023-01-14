#include <bits/stdc++.h>
const int M = 40005;
int temp[M], a[M], n, ans = 0;
void mergesort(int lo, int hi) {
  if (lo < hi) {
    int mid = ((lo + hi) >> 1);
    mergesort(lo, mid);
    mergesort(mid + 1, hi);
    int i = lo, j = mid + 1, k = lo;
    while (i <= mid && j <= hi) {
      if (a[i] <= a[j]) {
        temp[k++] = a[i++];
      } else {
        temp[k++] = a[j++];
        ans += mid - i + 1;
      }
    }
    while (i <= mid) temp[k++] = a[i++];
    while (j <= hi) temp[k++] = a[j++];
    for (int i = lo; i <= hi; i++) a[i] = temp[i];
  }
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  mergesort(1, n);
  printf("%d", ans);
  return 0;
}
