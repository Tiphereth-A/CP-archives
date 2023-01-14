#include <bits/stdc++.h>
using namespace std;
const int N = 25;
bool graph[N][N];
int n, a[N];
int max_ans, max_path[N], max_path_cnt;
int now_path[N];
bool vis[N];
void dfs(int x, int sum, int step = 1) {
  auto check = [](int x) {
    for (int i = 1; i <= n; ++i)
      if (graph[x][i] && !vis[i]) return false;
    return true;
  };
  if (check(x)) {
    if (max_ans < sum) {
      max_ans = sum;
      max_path_cnt = step;
      for (int i = 1; i <= step; ++i) max_path[i] = now_path[i];
    }
    return;
  }
  for (int i = 1; i <= n; ++i) {
    if (graph[x][i] && !vis[i]) {
      vis[i] = 1;
      now_path[step + 1] = i;
      dfs(i, sum + a[i], step + 1);
      vis[i] = 0;
    }
  }
}
int main() {
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = 1; i < n; ++i)
    for (int j = i + 1; j <= n; ++j) cin >> graph[i][j];
  for (int i = 1; i <= n; ++i) {
    vis[now_path[1] = i] = 1;
    dfs(i, a[i]);
    vis[i] = 0;
  }
  for (int i = 1; i <= max_path_cnt; ++i) cout << max_path[i] << ' ';
  cout << endl << max_ans;
  return 0;
}
