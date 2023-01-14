#include <cmath>
#include <cstdio>
const int N = 1e6 + 5;
bool vis[N];
int main() {
  for (int i = 2; i * i < N; ++i)
    if (!vis[i])
      for (int j = i * i; j < N; j += i) vis[j] = 1;
  int kase;
  scanf("%d", &kase);
  for (int cnt = 1; cnt <= kase; ++cnt) {
    int n, _;
    scanf("%d", &n);
    long long tot = 0;
    while (n--) {
      scanf("%d", &_);
      while (vis[++_]);
      tot += _;
    }
    printf("Case %d: %lld Xukha\n", cnt, tot);
  }
}
