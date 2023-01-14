#include <cstdio>
int cnt = 0;
int a[1005], b[1005];
void sort(int l, int r) {
  if (l >= r) return;
  int mid = (l + r) / 2;
  sort(l, mid);
  sort(mid + 1, r);
  int i = l, j = mid + 1, t = 0;
  while (i <= mid && j <= r)
    if (a[i] > a[j]) {
      b[t++] = a[j++];
      cnt += mid - i + 1;
    } else b[t++] = a[i++];
  while (i <= mid) b[t++] = a[i++];
  while (j <= r) b[t++] = a[j++];
  for (int i = 0; i < t; i++) a[l + i] = b[i];
}
int main() {
  int num;
  scanf("%d", &num);
  for (int k = 1; k <= num; k++, cnt = 0) {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    sort(0, n - 1);
    printf("Scenario #%d:\n%d\n\n", k, cnt);
  }
  return 0;
}
