#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e3 + 5;
int m, n, f[N];
int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }
void merge(int x, int y) { f[find(x)] = find(y); }
int main() {
  scanf("%d\n%d\n", &n, &m);
  _for(i, 1, n << 1) f[i] = i;
  int p, q;
  char relation;
  _for(i, 1, m) {
    scanf("%c%d%d\n", &relation, &p, &q);
    if (relation == 'F') merge(p, q);
    else {
      merge(q + n, p);
      merge(p + n, q);
    }
  }
  int cnt = 0;
  _for(i, 1, n)
    if (f[i] == i) ++cnt;
  printf("%d", cnt);
  return 0;
}
