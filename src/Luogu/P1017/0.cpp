#include <bits/stdc++.h>
using namespace std;
const char num[20] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                      'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
int main() {
  int n, m, r, i = 0;
  cin >> n >> r;
  cout << n << '=';
  if (n == 0) cout << '0';
  char c[111] = {0};
  while (n != 0 && n != -0) {
    m = n % r;
    n /= r;
    if (m < 0) {
      m -= r;
      n++;
    }
    c[i] = num[m];
    i++;
  }
  for (int j = i - 1; j >= 0; j--) cout << c[j];
  cout << "(base" << r << ")";
  return 0;
}
