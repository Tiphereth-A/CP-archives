#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin >> n;
  cout << string(13 * n + 19, '*') << endl;
  const string l = '*' + string(13 * n + 17, '.') + '*';
  for (int j = 1; j <= n; j++) cout << l << endl;
  vector<string> v(2 * n + 3, l);
  for (int j = 0; j < 2 * n + 3; j++) v[j][n + 2] = '@';
  for (int j = 0; j < 2 * n + 3; j++) v[j][3 * n + 4] = '@';
  for (int j = 0, k = n + 2; j < 2 * n + 3; j++, k++) v[j][k] = '@';
  for (int j = 0; j < 2 * n + 3; j++) v[j][4 * n + 6] = '@';
  for (int j = 4 * n + 6; j < 6 * n + 9; j++) v[0][j] = '@';
  for (int j = 4 * n + 6; j < 6 * n + 9; j++) v[n + 1][j] = '@';
  for (int j = 0; j < 2 * n + 3; j++) v[j][7 * n + 10] = '@';
  for (int j = 7 * n + 10; j < 9 * n + 13; j++) v[2 * n + 2][j] = '@';
  for (int j = 10 * n + 14; j < 12 * n + 17; j++) v[0][j] = '@';
  for (int j = 10 * n + 14; j < 12 * n + 17; j++) v[n + 1][j] = '@';
  for (int j = 10 * n + 14; j < 12 * n + 17; j++) v[2 * n + 2][j] = '@';
  for (int j = 0; j < n + 2; j++) v[j][10 * n + 14] = '@';
  for (int j = n + 2; j < 2 * n + 3; j++) v[j][12 * n + 16] = '@';
  for (auto &&s : v) cout << s << endl;
  for (int j = 1; j <= n; j++) cout << l << endl;
  cout << string(13 * n + 19, '*') << endl;
  return 0;
}
