#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
#define gi getint
#define gc getchar
using namespace std;
struct graph {
  int x, y, z;
} g[200005];
int pre[5005];
int find(int x) {
  int a = x, b = x, c;
  while (a != pre[a]) a = pre[a];
  while (b != pre[b]) {
    c = pre[b];
    pre[b] = a;
    b = c;
  }
  return a;
}
int getint() {
  int t = 0;
  char c = gc();
  while (c < 48 || c > 57) c = gc();
  while (c >= 48 && c <= 57) {
    t = (t << 3) + (t << 1) + (c ^ 48);
    c = gc();
  }
  return t;
}
bool cmp(graph a, graph b) { return a.z < b.z; }
int main() {
  int n = gi(), m = gi(), cnt = 0, ans = 0;
  _for(i, 1, m) {
    g[i].x = gi();
    g[i].y = gi();
    g[i].z = gi();
  }
  _for(i, 1, n) pre[i] = i;
  sort(g + 1, g + m + 1, cmp);
  _for(i, 1, m) {
    if (cnt == n - 1) break;
    int fx = find(g[i].x), fy = find(g[i].y);
    if (fx != fy) {
      ans += g[i].z;
      pre[fx] = fy;
      ++cnt;
    }
  }
  if (cnt < n - 1) cout << "orz";
  else cout << ans;
  return 0;
}
