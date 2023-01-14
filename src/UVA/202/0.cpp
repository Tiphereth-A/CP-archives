#include <cstdio>
#include <cstring>
int r[3003], u[3003], s[3003];
int main() {
  int n, m, t;
  while (scanf("%d%d", &n, &m) == 2) {
    t = n;
    memset(r, 0, sizeof(r));
    memset(u, 0, sizeof(u));
    int count = 0;
    r[count++] = n / m;
    n %= m;
    while (!u[n] && n) {
      u[n] = count;
      s[count] = n;
      r[count++] = 10 * n / m;
      n = 10 * n % m;
    }
    printf("%d/%d = %d", t, m, r[0]);
    printf(".");
    for (int i = 1; i < count && i <= 50; ++i) {
      if (n && s[i] == n) printf("(");
      printf("%d", r[i]);
    }
    if (!n) printf("(0");
    if (count > 50) printf("...");
    printf(")\n");
    printf("   %d = number of digits in repeating cycle\n\n",
           !n ? 1 : count - u[n]);
  }
  return 0;
}
