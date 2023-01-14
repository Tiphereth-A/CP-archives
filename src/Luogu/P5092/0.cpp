#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int fa[N], sum[N], num[N];
int find(int x) {
  if (x == fa[x]) return x;
  int fx = find(fa[x]);
  sum[x] += sum[fa[x]];
  return fa[x] = fx;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t, x, y, fx, fy;
  cin >> t;
  for (int i = 1; i < N; ++i) fa[i] = i;
  for (int i = 1; i < N; ++i) num[i] = 1;
  char op;
  while (t--) {
    cin >> op >> x;
    fx = find(x);
    if (op == 'M') {
      cin >> y;
      fy = find(y);
      sum[fx] += num[fy];
      num[fy] += num[fx];
      num[fx] = 0;
      fa[fx] = fy;
    } else cout << sum[x] << '\n';
  }
  return 0;
}
