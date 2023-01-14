#include <bits/stdc++.h>
using namespace std;
struct Node {
  int l, r, c;
  Node(int l, int r, int c): l(l), r(r), c(c) {}
  friend bool operator<(Node const &x, Node const &y) {
    return x.r == y.r ? x.l < y.l : x.r < y.r;
  }
};
int main() {
  int n, m;
  cin >> n >> m;
  vector<Node> a;
  a.reserve(m + 1);
  a.emplace_back(0, 0, 0);
  for (int i = 1, l, r, c; i <= m; ++i) {
    cin >> l >> r >> c;
    a.emplace_back(l, r, c);
  }
  sort(a.begin() + 1, a.end());
  int ans = 0;
  vector<bool> vis(n + 1);
  for (int i = 1, k; i <= m; ++i) {
    k = 0;
    for (int j = a[i].r; j >= a[i].l; --j) k += vis[j];
    if (k >= a[i].c) continue;
    for (int j = a[i].r; (j >= a[i].r - a[i].c + 1) && (k < a[i].c); --j)
      if (!vis[j]) {
        vis[j] = 1;
        ++ans;
        ++k;
      }
  }
  cout << ans;
}
