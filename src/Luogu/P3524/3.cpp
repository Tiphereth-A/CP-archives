#include <bits/stdc++.h>
using namespace std;
const int N = 3e3 + 5;
bool g[N][N];
struct node {
  int in, id;
  bool operator<(const node &rhs) const { return in > rhs.in; }
} deg[N];
int ans[N];
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i) deg[i].id = i;
  for (int i = 1, x, y; i <= m; ++i) {
    scanf("%d%d", &x, &y);
    g[x][y] = g[y][x] = 1;
    ++deg[x].in;
    ++deg[y].in;
  }
  sort(deg + 1, deg + n + 1);
  mt19937 g(time(0));
  shuffle(deg + 1, deg + n / 3 * 2 + 1, g);
  sort(deg + 1, deg + n / 3 + 1, [](const node &a, const node &b) {
    return a.id < b.id;
  });
  for (int i = 1; i <= n / 3; ++i) printf("%d%c", deg[i].id, " \n"[i == n / 3]);
  return 0;
}
