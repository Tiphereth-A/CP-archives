#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
template <class T>
bool chkmin(T &a, T b) {
  return b < a ? a = b, true : false;
}
template <class T>
bool chkmax(T &a, T b) {
  return a < b ? a = b, true : false;
}
const int OFFSET = 5;
const int N = 3e5 + OFFSET, M = 1e6, K = 21;
template <typename _T = std::ptrdiff_t,
          const std::size_t _N = N,
          const bool _clear = false>
class BIT {
private:
  _T tree[_N];
  std::size_t lowbit(std::ptrdiff_t x) { return x & (-x); }

public:
  BIT() {
    if (_clear) memset(tree, 0, sizeof(tree));
  }
  void clear() { memset(tree, 0, sizeof(tree)); }
  void add(std::size_t pos, _T val = 1) {
    for (std::size_t i = pos; i < _N; i += lowbit(i)) tree[i] += val;
  }
  _T query(std::size_t pos) {
    _T ret = 0;
    for (std::size_t i = pos; i; i = (std::ptrdiff_t)i - lowbit(i))
      ret += tree[i];
    return ret;
  }
};
BIT<i64, N * 2> tr;
int fa[N];
int find(int x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
void merge(int x, int y) { fa[find(x)] = find(y); }
i64 d[M + OFFSET];
i64 a[N] = {0, 1, 2};
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  _for(i, 1, M)
    for (int j = i; j <= M; j += i) ++d[j];
  _for(i, 1, n) {
    fa[i] = i;
    scanf("%lld", a + i);
    tr.add(i, a[i]);
  }
  fa[n + 1] = n + 1;
  int op, l, r;
  _for(i, 1, m) {
    scanf("%d%d%d", &op, &l, &r);
    if (op == 1) {
      for (int i = l; i <= r; i = find(i) == i ? i + 1 : fa[i]) {
        tr.add(i, d[a[i]] - a[i]);
        if ((a[i] = d[a[i]]) <= 2) fa[i] = i + 1;
      }
    } else printf("%lld\n", tr.query(r) - tr.query(l - 1));
  }
  return 0;
}
