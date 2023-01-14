#include <bits/stdc++.h>
using namespace std;
int s[21][21][21] = {0};
long long a, b, c;
int w(long long a, long long b, long long c) {
  if (a <= 0 || b <= 0 || c <= 0) {
    return 1;
  } else if (a > 20 || b > 20 || c > 20) {
    return w(20, 20, 20);
  } else if (s[a][b][c] == 0) {
    if (a < b && b < c) {
      s[a][b][c] = w(a, b, c - 1) + w(a, b - 1, c - 1) - w(a, b - 1, c);
    } else {
      s[a][b][c] = w(a - 1, b, c) + w(a - 1, b - 1, c) + w(a - 1, b, c - 1) -
                   w(a - 1, b - 1, c - 1);
    }
  }
  return s[a][b][c];
}
int main() {
  cin >> a >> b >> c;
  while (a != -1 || b != -1 || c != -1) {
    printf("w(%lld, %lld, %lld) = %d\n", a, b, c, w(a, b, c));
    cin >> a >> b >> c;
  }
  return 0;
}
