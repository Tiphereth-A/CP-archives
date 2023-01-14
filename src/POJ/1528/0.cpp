#include <cmath>
#include <cstdio>
const char status[][15] = {"DEFICIENT", "PERFECT", "ABUNDANT"};
int main() {
  puts("PERFECTION OUTPUT");
  int n;
  while (scanf("%d", &n) && n) {
    if (n == 1) {
      puts("    1  DEFICIENT");
      continue;
    }
    int cnt = 1;
    for (int i = 2; i <= sqrt(n + 0.5); ++i)
      if (n % i == 0) {
        cnt += i;
        if (i != n / i) cnt += n / i;
      }
    printf("%5d  %s\n", n, status[(n < cnt) + (n <= cnt)]);
  }
  puts("END OF OUTPUT");
  return 0;
}
