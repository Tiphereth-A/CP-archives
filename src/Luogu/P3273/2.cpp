#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <set>
using namespace std;
int read() {
  int x;
  cin >> x;
  return x;
}
const int N = 300010;
struct Node {
  int val, ch[2], d, fa;
} t[N];
int &rs(int x);
int merge(int x, int y);
void pushup(int x);
void pushdown(int x, int y);
int find(int x);
int n, m, f[N], tag[N], siz[N], delta;
char op[10];
multiset<int> s;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int i, x, y;
  n = read();
  for (i = 1; i <= n; ++i) {
    t[i].val = read();
    f[i] = i;
    siz[i] = 1;
    s.insert(t[i].val);
  }
  m = read();
  while (m--) {
    cin >> op;
    if (op[0] == 'U') {
      x = find(read());
      y = find(read());
      if (x != y) {
        if (siz[x] > siz[y]) swap(x, y);
        pushdown(x, tag[x] - tag[y]);
        f[x] = f[y] = merge(x, y);
        if (f[x] == x) {
          s.erase(s.find(t[y].val + tag[y]));
          tag[x] = tag[y];
          siz[x] += siz[y];
          tag[y] = siz[y] = 0;
        } else {
          s.erase(s.find(t[x].val + tag[y]));
          siz[y] += siz[x];
          tag[x] = siz[x] = 0;
        }
      }
    } else if (op[0] == 'A') {
      if (op[1] == '1') {
        x = read();
        if (x == find(x)) {
          t[t[x].ch[0]].fa = t[t[x].ch[1]].fa = 0;
          y = merge(t[x].ch[0], t[x].ch[1]);
          s.erase(s.find(t[x].val + tag[x]));
          t[x].val += read();
          t[x].fa = t[x].ch[0] = t[x].ch[1] = 0;
          t[x].d = 1;
          f[x] = f[y] = merge(x, y);
          s.insert(t[f[x]].val + tag[x]);
          if (f[x] == y) {
            tag[y] = tag[x];
            siz[y] = siz[x];
            tag[x] = siz[x] = 0;
          }
        } else {
          t[t[x].ch[0]].fa = t[t[x].ch[1]].fa = t[x].fa;
          t[t[x].fa].ch[x == t[t[x].fa].ch[1]] = merge(t[x].ch[0], t[x].ch[1]);
          t[x].val += read();
          t[x].fa = t[x].ch[0] = t[x].ch[1] = 0;
          t[x].d = 1;
          y = find(x);
          f[x] = f[y] = merge(x, y);
          if (f[x] == x) {
            s.erase(s.find(t[y].val + tag[y]));
            s.insert(t[x].val + tag[y]);
            tag[x] = tag[y];
            siz[x] = siz[y];
            tag[y] = siz[y] = 0;
          }
        }
      } else if (op[1] == '2') {
        x = find(read());
        s.erase(s.find(t[x].val + tag[x]));
        tag[x] += read();
        s.insert(t[x].val + tag[x]);
      } else delta += read();
    } else {
      if (op[1] == '1') {
        x = read();
        cout << t[x].val + tag[find(x)] + delta << '\n';
      } else if (op[1] == '2') {
        x = find(read());
        cout << t[x].val + tag[x] + delta << '\n';
      } else cout << *s.rbegin() + delta << '\n';
    }
  }
  return 0;
}
int &rs(int x) { return t[x].ch[t[t[x].ch[1]].d < t[t[x].ch[0]].d]; }
int merge(int x, int y) {
  if (!x || !y) return x | y;
  if (t[x].val < t[y].val) swap(x, y);
  t[rs(x) = merge(rs(x), y)].fa = x;
  pushup(x);
  return x;
}
void pushup(int x) {
  if (!x) return;
  if (t[x].d != t[rs(x)].d + 1) {
    t[x].d = t[rs(x)].d + 1;
    pushup(t[x].fa);
  }
}
void pushdown(int x, int y) {
  if (!x) return;
  t[x].val += y;
  pushdown(t[x].ch[0], y);
  pushdown(t[x].ch[1], y);
}
int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }
