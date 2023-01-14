#include <cstdio>
const int N = 3e4 + 5;
const int table[] = {5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000};
unsigned long long f[N] = {1};
int main() {
  for (int j = 0; j < sizeof(table) / sizeof(table[0]); ++j)
    for (int i = 1; i <= 30000; ++i)
      if (i >= table[j]) f[i] += f[i - table[j]];
  int a, b;
  while (scanf("%d.%d", &a, &b) && (a || b))
    printf("%3d.%02d%17llu\n", a, b, f[a * 100 + b]);
}
