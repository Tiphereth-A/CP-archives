#include <bits/stdc++.h>
#define N 2000005
struct p {
  int index, n;
} a[N];
int m, n;
int head, tail;
int main() {
  scanf("%d%d", &n, &m);
  printf("0\n");
  int tmp;
  scanf("%d", &tmp);
  a[tail++].n = tmp;
  for (int i = 1; i < n; ++i) {
    if (i - a[head].index > m) ++head;
    printf("%d\n", a[head].n);
    scanf("%d", &tmp);
    while (tail >= head && tmp < a[--tail].n);
    a[++tail].n = tmp;
    a[tail++].index = i;
  }
  return 0;
}
