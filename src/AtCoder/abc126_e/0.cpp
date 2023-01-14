#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int fa[N];
int find(int x) { return x == fa[x] ? fa[x] : fa[x] = find(fa[x]); }
void merge(int x, int y) { fa[find(x)] = find(y); }
int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) fa[i] = i;
  for (int i = 1, x, y, z; i <= m; ++i) {
    cin >> x >> y >> z;
    merge(x, y);
  }
  int ans = 0;
  for (int i = 1; i <= n; ++i) ans += fa[i] == i;
  cout << ans;
  return 0;
}
