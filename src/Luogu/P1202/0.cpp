#include <bits/stdc++.h>
using namespace std;
int day[8] = {0};
int mon[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int main() {
  int n, week = 1;
  cin >> n;
  for (int i = 1900; i < 1900 + n; ++i) {
    if ((!(i % 4) && (i % 100)) || !(i % 400)) mon[1] = 29;
    else mon[1] = 28;
    for (int j = 0; j < 12; ++j) {
      for (int c = 1; c <= mon[j]; ++c) {
        if (c == 13) ++day[week];
        ++week;
        if (week > 7) week = 1;
      }
    }
  }
  cout << day[6] << " " << day[7] << " ";
  for (int i = 1; i <= 5; ++i) cout << day[i] << " ";
  return 0;
}
