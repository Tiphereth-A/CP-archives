#include <bits/stdc++.h>
#define M 100005
#define _for(i, l, r) for (int i = (l); i <= (r); i++)
#define max(a, b) (((a) > (b)) ? (a) : (b))
using namespace std;
int f[M], n, m, v[M], p[M];
int main() {
  scanf("%d %d", &n, &m);
  _for(i, 1, m) { scanf("%d %d", &v[i], &p[i]); }
  _for(i, 1, m)
    _for(j, 0, n) {
      if (j >= v[i]) f[j] = max(f[j - v[i]] + p[i], f[j]);
    }
  printf("%d", f[n]);
  return 0;
}
