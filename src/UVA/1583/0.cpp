#include <cstdio>
#define N 100005
int ans[N];
int main() {
  for (int i = 1; i < N; ++i) {
    int x = i, y = i;
    while (x) {
      y += x % 10;
      x /= 10;
    }
    if (ans[y] == 0 || ans[y] > i) ans[y] = i;
  }
  int n;
  scanf("%d", &n);
  while (n--) {
    int m;
    scanf("%d", &m);
    printf("%d\n", ans[m]);
  }
  return 0;
}
