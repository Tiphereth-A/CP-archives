#include <bits/stdc++.h>
using namespace std;
char map[105][105];
int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; ++i) cin >> map[i];
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      if (map[i][j] == '-') continue;
      map[i][j] = ((i + j) & 1) ? 'W' : 'B';
    }
  for (int i = 0; i < n; ++i) cout << map[i] << endl;
  return 0;
}
