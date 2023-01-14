#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
#define _for(i, pre, suf, vals...) \
  for (decltype(pre + suf) i = (pre), i##end = (suf), ##vals; i <= i##end; ++i)
#define _rfor(i, suf, pre, vals...)                                          \
  for (make_signed_t<decltype(suf - pre)> i = (suf), i##end = (pre), ##vals; \
       i >= i##end;                                                          \
       --i)
const int N = 3e3 + 5;
int tr[N * N];
int cnt_a;
void add(int x, int v) {
  for (; x <= cnt_a; x += x & -x) tr[x] += v;
}
int query(int x) {
  int res = 0;
  for (; x; x -= x & -x) res += tr[x];
  return res;
}
struct node {
  int id, num;
  bool operator<(const node &rhs) const { return num < rhs.num; }
} a[N * N];
struct note {
  int pre, suf, id, val;
  bool operator<(const note &rhs) const { return val < rhs.val; }
} b[N * N];
int pre[N][N], suf[N][N], diag[N][N], id[N][N];
bool maps[N][N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, m;
  cin >> n >> m;
  _for(i, 1, n)
    _for(j, 1, m) {
      char ch;
      cin >> ch;
      maps[i][j] = ch == 'z';
    }
  _for(i, 1, n)
    _for(j, 1, m)
      if (maps[i][j]) pre[i][j] = pre[i][j - 1] + 1;
  _for(i, 1, n)
    _rfor(j, m, 1)
      if (maps[i][j]) suf[i][j] = suf[i][j + 1] + 1;
  _rfor(i, n, 1)
    _for(j, 1, m)
      if (maps[i][j]) diag[i][j] = diag[i + 1][j - 1] + 1;
  _for(k, 1, m)
    for (int i = 1, j = k; j >= 1 && i <= n; ++i, --j)
      a[id[i][j] = ++cnt_a] = {cnt_a, i - suf[i][j] + 1};
  _for(k, 2, n)
    for (int i = k, j = m; j >= 1 && i <= n; ++i, --j)
      a[id[i][j] = ++cnt_a] = {cnt_a, i - suf[i][j] + 1};
  sort(a + 1, a + 1 + cnt_a);
  int cnt_b = 0;
  _for(i, 1, n, len)
    _for(j, 1, m) {
      if (!(len = min(pre[i][j], diag[i][j]))) continue;
      b[++cnt_b] = {id[i][j], id[i + len - 1][j - len + 1], cnt_b, i + 1};
    }
  sort(b + 1, b + 1 + cnt_b);
  i64 ans = 0;
  _for(i, 1, cnt_b, k = 1) {
    while (k <= cnt_a && a[k].num < b[i].val) {
      add(a[k].id, 1);
      ++k;
    }
    ans += query(b[i].suf) - query(b[i].pre - 1);
  }
  cout << ans << '\n';
  return 0;
}
