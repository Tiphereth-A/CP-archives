#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
using namespace std;
const int N = 5e4 + 5;
struct Edge {
  int to, next;
} e[N + N];
int head[N], cnt_edge;
void addEdge(int u, int v) {
  e[cnt_edge].to = v;
  e[cnt_edge].next = head[u];
  head[u] = cnt_edge++;
}
struct Node {
  int tag, l, r;
} a[N * 4];
void push_up(int rt) {
  a[rt].tag = (a[rt << 1].tag == a[(rt << 1) | 1].tag) ? a[rt << 1].tag : -1;
}
void build(int rt, int l, int r) {
  a[rt].l = l;
  a[rt].r = r;
  a[rt].tag = -1;
  if (l == r) return;
  int mid = (a[rt].l + a[rt].r) >> 1;
  build(rt << 1, l, mid);
  build((rt << 1) | 1, mid + 1, r);
  push_up(rt);
}
void push_down(int rt) {
  a[rt << 1].tag = a[rt].tag;
  a[(rt << 1) | 1].tag = a[rt].tag;
  a[rt].tag = -1;
}
void modify(int rt, int l, int r, int val) {
  if (a[rt].l == l && a[rt].r == r) {
    a[rt].tag = val;
    return;
  }
  if (~a[rt].tag) push_down(rt);
  int mid = (a[rt].l + a[rt].r) / 2;
  if (r <= mid) {
    modify(rt << 1, l, r, val);
  } else if (mid < l) {
    modify((rt << 1) | 1, l, r, val);
  } else {
    modify(rt << 1, l, mid, val);
    modify((rt << 1) | 1, mid + 1, r, val);
  }
  push_up(rt);
}
int query(int rt, int pos) {
  if (a[rt].l == pos && a[rt].r == pos) return a[rt].tag;
  if (~a[rt].tag) push_down(rt);
  int mid = (a[rt].l + a[rt].r) / 2;
  return pos <= mid ? query(rt << 1, pos) : query((rt << 1) | 1, pos);
}
int l[N], r[N], key, deg[N];
void dfs(int u) {
  l[u] = ++key;
  for (int i = head[u]; ~i; i = e[i].next) dfs(e[i].to);
  r[u] = key;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t_;
  cin >> t_;
  for (int kase = 1, n, m; kase <= t_; kase++) {
    memset(head, 0xff, sizeof(head));
    cnt_edge = key = 0;
    memset(deg, 0, sizeof(deg));
    cin >> n;
    for (int i = 0, u, v; i < n - 1; ++i) {
      cin >> u >> v;
      addEdge(v, u);
      ++deg[u];
    }
    int root = 0;
    for (int i = 1; i <= n; ++i)
      if (!deg[i]) {
        root = i;
        break;
      }
    dfs(root);
    build(1, 1, key);
    cin >> m;
    cout << "Case #" << kase << ":\n";
    for (int i = 0, x, y; i < m; ++i) {
      char op;
      cin >> op;
      if (op == 'C') {
        cin >> x;
        cout << query(1, l[x]) << '\n';
      } else {
        cin >> x >> y;
        modify(1, l[x], r[x], y);
      }
    }
  }
  return 0;
}
