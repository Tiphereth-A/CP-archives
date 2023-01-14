#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), i##end = (r), ##vals; i <= i##end; ++i)
const uint32_t N = 1e5 + 5;
int fa[N];
int find(int x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
void merge(int x, int y) { fa[find(x)] = find(y); }
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, q;
  cin >> n >> q;
  _for(i, 1, n) fa[i] = i;
  _for(i, 1, q, x, y) {
    cin >> x >> y;
    merge(x - 1, y);
  }
  cout << (find(0) == find(n) ? "Yes" : "No");
  return 0;
}
