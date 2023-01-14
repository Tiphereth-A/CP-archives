#include <bits/stdc++.h>
using namespace std;
int x[4], y[4], z[4];
void dfs(int c1, int c2, int c3, int num, int a, int b, int c, int last) {
  if (!a && !b && !c) {
    cout << c1 << ' ' << c2 << ' ' << c3 << ' ' << num;
    exit(0);
  }
  for (int i = last; i <= 3; ++i) {
    if (a - x[i] >= 0 && b - y[i] >= 0 && c - z[i] >= 0) {
      if (i == 1) dfs(c1 + 1, c2, c3, num, a - x[i], b - y[i], c - z[i], 1);
      if (i == 2) dfs(c1, c2 + 1, c3, num, a - x[i], b - y[i], c - z[i], 2);
      if (i == 3) dfs(c1, c2, c3 + 1, num, a - x[i], b - y[i], c - z[i], 3);
    }
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int a, b, c;
  cin >> a >> b >> c;
  for (int i = 1; i <= 3; ++i) cin >> x[i] >> y[i] >> z[i];
  for (int i = 1; i < 100; ++i) dfs(0, 0, 0, i, a * i, b * i, c * i, 1);
  cout << "NONE";
  return 0;
}
