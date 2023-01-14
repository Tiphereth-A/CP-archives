#include <cmath>
#include <cstdio>
#include <cstring>
const int N = 2e4 + 5;
bool vis[N];
int pri[N], cnt_pri = 0;
bool judge(int a, int b) {
  if (a == 0) return 0;
  int _ = a * a + 2 * b * b;
  for (int i = 0; i < cnt_pri && pri[i] < _; ++i)
    if (_ % pri[i] == 0) return 0;
  return 1;
}
int main() {
  vis[1] = 1;
  for (int i = 2; i < N; ++i) {
    if (vis[i]) continue;
    pri[cnt_pri++] = i;
    for (int j = i * i; j < N; j += i) { vis[j] = 1; }
  }
  int kase;
  scanf("%d", &kase);
  while (kase--) {
    int a, b;
    scanf("%d%d", &a, &b);
    printf("%s\n", judge(a, b) ? "Yes" : "No");
  }
  return 0;
}
