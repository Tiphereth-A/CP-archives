#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
int P[10001];
int I[10001];
int Min, Leaf;
void dfs(int il, int ir, int pl, int pr, int value) {
  int f = il, L, R;
  while (I[f] != P[pr]) ++f;
  if (f > il) dfs(il, f - 1, pl, pl + f - il - 1, value + P[pr]);
  if (f < ir) dfs(f + 1, ir, pl + f - il, pr - 1, value + P[pr]);
  if (pl == pr) {
    if (Min > P[pl] + value) {
      Min = P[pl] + value;
      Leaf = P[pl];
    } else if (Min == P[pl] + value && Leaf > P[pl]) Leaf = P[pl];
  }
}
int main() {
  char ch;
  while (~scanf("%d", &I[0])) {
    int count = 1;
    while (getchar() != '\n') scanf("%d", &I[count++]);
    for (int i = 0; i < count; ++i) scanf("%d%c", &P[i], &ch);
    Min = 100000001;
    Leaf = -1;
    dfs(0, count - 1, 0, count - 1, 0);
    printf("%d\n", Leaf);
  }
  return 0;
}
