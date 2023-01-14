#include <bits/stdc++.h>
using namespace std;
int A, B, C;
int vis[22][22][22];
int rec[22];
void dfs(int a, int b, int c) {
  if (vis[a][b][c] == 1) return;
  else vis[a][b][c] = 1;
  if (a == 0 && rec[c] == 0) rec[c] = 1;
  if (c >= (A - a)) dfs(A, b, c - (A - a));
  else dfs(c + a, b, 0);
  if (c >= (B - b)) dfs(a, B, c - (B - b));
  else dfs(a, c + b, 0);
  if (b >= (A - a)) dfs(A, b - (A - a), c);
  else dfs(b + a, 0, c);
  if (b >= (C - c)) dfs(a, b - (C - c), C);
  else dfs(a, 0, b + c);
  if (a >= (C - c)) dfs(a - (C - c), b, C);
  else dfs(0, b, a + c);
  if (a >= (B - b)) dfs(a - (B - b), B, c);
  else dfs(0, a + b, c);
}
int main() {
  cin >> A >> B >> C;
  dfs(0, 0, C);
  for (int i = 0; i <= 21; i++)
    if (rec[i]) cout << i << ' ';
  return 0;
}
