#include <bits/stdc++.h>
using namespace std;
int a[25][25] = {1};
int main() {
  int n;
  cin >> n;
  for (int i = 1; i < n; ++i) {
    a[i][0] = a[i][i] = 1;
    for (int j = 1; j < n; ++j) a[i][j] = a[i - 1][j] + a[i - 1][j - 1];
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= i; ++j) printf("%d ", a[i][j]);
    puts("");
  }
  return 0;
}
