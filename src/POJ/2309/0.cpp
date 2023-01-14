#include <cstdio>
#define lowbit(x) ((x) & (-x))
int main() {
  int kase;
  scanf("%d", &kase);
  while (kase--) {
    int k;
    scanf("%d", &k);
    printf("%d %d\n", k - lowbit(k) + 1, k + lowbit(k) - 1);
  }
}
