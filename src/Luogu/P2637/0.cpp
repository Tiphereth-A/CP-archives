#include <bits/stdc++.h>
int N, M, m, n, P_i[1000], p, q, price, total;
int main() {
  scanf("%d%d", &N, &M);
  for (m = 0; m < M; ++m) scanf("%d", &P_i[m]);
  for (n = total = 0; n < M; ++n) {
    p = P_i[n];
    q = 0;
    for (m = 0; m < M; ++m)
      if (P_i[m] >= p) ++q;
    q = q > N ? N : q;
    if (p * q > total) {
      total = p * q;
      price = p;
    }
  }
  printf("%d %d\n", price, total);
  return 0;
}
