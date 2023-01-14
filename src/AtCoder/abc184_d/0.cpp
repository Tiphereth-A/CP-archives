#include <bits/stdc++.h>
using namespace std;
const int N = 105;
double dp[N][N][N];
double f(int a, int b, int c) {
  if (a == 100 || b == 100 || c == 100) return dp[a][b][c] = 0;
  if (dp[a][b][c] >= 0) return dp[a][b][c];
  return dp[a][b][c] = 1.0 * a / (a + b + c) * f(a + 1, b, c) +
                       1.0 * b / (a + b + c) * f(a, b + 1, c) +
                       1.0 * c / (a + b + c) * f(a, b, c + 1) + 1;
}
int main() {
  int a, b, c;
  cin >> a >> b >> c;
  for (int i = a; i < N; ++i)
    for (int j = b; j < N; ++j)
      for (int k = c; k < N; ++k) dp[i][j][k] = -1;
  printf("%.9lf", f(a, b, c));
  return 0;
}
