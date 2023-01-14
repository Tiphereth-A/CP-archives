#include <iostream>
using namespace std;
const int N = 1000010;
struct Node {
  int val, ch[2], d;
} t[N];
int &rs(int x) { return t[x].ch[t[t[x].ch[1]].d < t[t[x].ch[0]].d]; }
int merge(int x, int y) {
  if (!x || !y) return x | y;
  if (t[x].val > t[y].val) swap(x, y);
  t[x].ch[1] = merge(t[x].ch[1], y);
  if (t[t[x].ch[1]].d > t[t[x].ch[0]].d) swap(t[x].ch[0], t[x].ch[1]);
  t[x].d = t[rs(x)].d + 1;
  return x;
}
int f[N];
int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }
bool kill[N];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> t[i].val;
    f[i] = i;
  }
  int m;
  cin >> m;
  int x, y;
  char op;
  while (m--) {
    cin >> op;
    if (op == 'M') {
      cin >> x >> y;
      if (kill[x] || kill[y]) continue;
      x = find(x);
      y = find(y);
      if (x != y) f[x] = f[y] = merge(x, y);
    } else {
      cin >> x;
      if (!kill[x]) {
        x = find(x);
        kill[x] = true;
        f[x] = f[t[x].ch[0]] = f[t[x].ch[1]] = merge(t[x].ch[0], t[x].ch[1]);
        cout << t[x].val << '\n';
      } else cout << "0\n";
    }
  }
  return 0;
}
