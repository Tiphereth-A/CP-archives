#include <bits/stdc++.h>
#define N 32005
int n, m;
int f[N];
struct node {
  int v, w;
} a1[N], a2[3][N];
int num2[N];
int max(int a, int b) { return a > b ? a : b; }
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; ++i) {
    int v, p, q;
    scanf("%d%d%d", &v, &p, &q);
    if (q) {
      a2[++num2[q]][q].v = v;
      a2[num2[q]][q].w = v * p;
    } else {
      a1[i].v = v;
      a1[i].w = v * p;
    }
  }
  for (int i = 1; i <= m; ++i) {
    int a1v = a1[i].v, a1w = a1[i].w;
    for (int j = n; a1v && j >= a1v; --j) {
      int a2v1 = a2[1][i].v, a2w1 = a2[1][i].w;
      int a2v2 = a2[2][i].v, a2w2 = a2[2][i].w;
      f[j] = max(f[j], f[j - a1v] + a1w);
      if (j >= a1v + a2v1) f[j] = max(f[j], f[j - a1v - a2v1] + a1w + a2w1);
      if (j >= a1v + a2v2) f[j] = max(f[j], f[j - a1v - a2v2] + a1w + a2w2);
      if (j >= a1v + a2v1 + a2v2)
        f[j] = max(f[j], f[j - a1v - a2v1 - a2v2] + a1w + a2w1 + a2w2);
    }
  }
  printf("%d", f[n]);
  return 0;
}
