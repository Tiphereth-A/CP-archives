#include <bits/stdc++.h>
typedef long long ll;
#define MAXN 105
#define _for(i, l, r) for (int i = (l); i <= (r); i++)
using namespace std;
ll h[MAXN][MAXN];
int main() {
  int n;
  cin >> n;
  _for(i, 0, n) h[0][i] = 1;
  _for(i, 1, n)
    _for(j, i, n) {
      if (i == j) h[i][j] = h[i - 1][j];
      else h[i][j] = h[i - 1][j] + h[i][j - 1];
      h[i][j] %= 100;
    }
  cout << h[n][n];
  return 0;
}
