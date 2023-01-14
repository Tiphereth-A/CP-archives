#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
#define _rfor(i, r, l) for (decltype(l + r) i = (r); i >= (l); --i)
const int OFFSET = 5;
const int N = 1e6 + OFFSET;
int fa[N];
int find(int x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
void merge(int x, int y) { fa[find(x)] = find(y); }
int ans[N];
int main() {
  int n, m, p, q;
  scanf("%d%d%d%d", &n, &m, &p, &q);
  _for(i, 1, n) fa[i] = i;
  int l, r;
  _rfor(i, m, 1) {
    l = (1ll * i * p + q) % n + 1;
    r = (1ll * i * q + p) % n + 1;
    if (l > r) swap(l, r);
    for (int j = r; j >= l; j = fa[j])
      if (find(j) == j) {
        ans[j] = i;
        merge(j, j - 1);
      }
  }
  _for(i, 1, n) printf("%d\n", ans[i]);
  return 0;
}
