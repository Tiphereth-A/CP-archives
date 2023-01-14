#include <bits/stdc++.h>
#define M 1000001
#define _for(i, l, r) for (int i = (l); i <= (r); i++)
#define _rfor(i, r, l) for (int i = (r); i >= (l); i--)
#define max(a, b) (((a) > (b)) ? (a) : (b))
using namespace std;
int f[M], n, m, v[M], p[M];
int main() {
  ios::sync_with_stdio(false);
  scanf("%d %d", &n, &m);
  _for(i, 1, m) {
    scanf("%d %d", &v[i], &p[i]);
    p[i] *= v[i];
  }
  _for(i, 1, m)
    _rfor(j, n - v[i], 0) { f[j + v[i]] = max(f[j] + p[i], f[j + v[i]]); }
  printf("%d", f[n]);
  return 0;
}
