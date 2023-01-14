#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r, vals...) \
  for (decltype(l + r) i = (l), ##vals; i <= (r); ++i)
int f[100][100] = {1};
const int frac[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};
int main() {
  int n, r;
  cin >> n >> r;
  _for(i, 1, n)
    _for(j, 1, r) f[i][j] = f[i - 1][j - 1] + j * f[i - 1][j];
  cout << f[n][r] * frac[r];
  return 0;
}
