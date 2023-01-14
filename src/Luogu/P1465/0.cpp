#include <bits/stdc++.h>
using namespace std;
const string s[5][11] = {
  {},
  {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
  {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
  {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
  {"", "M", "MM", "MMM"}};
const string ap = "IVXLCDM";
int c[300];
void Count(string s) {
  for (unsigned i = 0; i < s.size(); i++) c[(unsigned)s[i]]++;
}
void Calc(int n) {
  int now = 1;
  while (n > 0) {
    Count(s[now][n % 10]);
    now++;
    n /= 10;
  }
}
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) Calc(i);
  for (unsigned i = 0; i < ap.size(); i++)
    if (c[(unsigned)ap[i]] > 0) printf("%c %d\n", ap[i], c[(unsigned)ap[i]]);
  return 0;
}
