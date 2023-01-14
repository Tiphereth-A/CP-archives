#include <bits/stdc++.h>
using namespace std;
int main() {
  char c[11];
  scanf("%c-%c%c%c-%c%c%c%c%c-%c",
        &c[1],
        &c[2],
        &c[3],
        &c[4],
        &c[5],
        &c[6],
        &c[7],
        &c[8],
        &c[9],
        &c[10]);
  int i[11];
  i[0] = 0;
  for (int j = 1; j < 10; j++) {
    i[j] = c[j] - '0';
    i[0] += i[j] * j;
  };
  i[0] %= 11;
  if ((i[0] + '0') == c[10]) cout << "Right";
  else if (i[0] == 10 && c[10] == 'X') cout << "Right";
  else {
    cout << i[1] << '-' << i[2] << i[3] << i[4] << '-' << i[5] << i[6] << i[7]
         << i[8] << i[9] << '-';
    if (i[0] == 10) cout << 'X';
    else cout << i[0];
  };
  return 0;
}
