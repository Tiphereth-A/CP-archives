#include <cstdio>
#include <cstring>
const int S = 1 << 8, mers_exp[] = {2, 3, 5, 7, 13, 17, 19, 31};
#define mers_pri(i) ((1 << mers_exp[i]) - 1)
int judge(int n) {
  int ans = 0;
  for (int i = 0; i < 8; ++i)
    if (n % mers_pri(i) == 0) {
      ans |= (1 << i);
      n /= mers_pri(i);
    }
  return n == 1 ? ans : 0;
}
bool f[S];
int status[S];
int main() {
  int k;
  while (~scanf("%d", &k)) {
    memset(f, 0, sizeof(f));
    int cnt_status = 0;
    for (int i = 1, _; i <= k; ++i) {
      scanf("%d", &_);
      if (_ = judge(_)) f[status[++cnt_status] = _] = 1;
    }
    for (int i = 1; i <= cnt_status; ++i)
      for (int j = 0; j < S; ++j)
        if (f[j] && !(j & status[i])) f[j | status[i]] = 1;
    int ans = 0;
    for (int i = S - 1, _ = 0; i; --i, _ = 0)
      if (f[i]) {
        for (int j = 0; j < 8; ++j)
          if ((1 << j) & i) _ += mers_exp[j];
        ans < _ ? ans = _ : 0;
      }
    if (ans) printf("%d\n", ans);
    else puts("NO");
  }
}
