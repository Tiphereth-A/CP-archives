#include <iostream>
#include <cstdio>
#include <ctype.h>
#include <math.h>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>
#include <sstream>
#include <queue>
#include <stack>
#define ll long long
#define N 1005
#define max(a, b) (((a) > (b)) ? (a) : (b))
using namespace std;
int r;
ll a[N][N], g[N][N];
ll f(int i, int j) {
  return g[i][j] >= 0 ?
           g[i][j] :
           g[i][j] =
             (i == r ? a[i][j] : max(f(i + 1, j), f(i + 1, j + 1)) + a[i][j]);
}
int main() {
  cin >> r;
  for (int i = 1; i <= r; i++)
    for (int j = 1; j <= i; j++) {
      cin >> a[i][j];
      g[i][j] = -1;
    }
  cout << f(1, 1);
  return 0;
}
