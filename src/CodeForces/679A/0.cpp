#include <bits/stdc++.h>
using namespace std;
string ans;
int i, cnt = 0;
int a[19] = {
  2, 3, 4, 5, 9, 7, 11, 13, 17, 19, 23, 25, 29, 31, 37, 41, 43, 47, 49};
int main() {
  ios::sync_with_stdio(false);
  for (i = 0; i <= 18; ++i) {
    cout << a[i] << endl;
    fflush(stdout);
    cin >> ans;
    if (ans[0] == 'y') { ++cnt; }
    if (cnt >= 2) {
      cout << "composite";
      return 0;
    }
  }
  cout << "prime";
  return 0;
}
