#include <bits/stdc++.h>
typedef unsigned long long ull;
using namespace std;
const string s[27] = {"zero",    "one",     "two",       "three",    "four",
                      "five",    "six",     "seven",     "eight",    "nine",
                      "ten",     "eleven",  "twelve",    "thirteen", "fourteen",
                      "fifteen", "sixteen", "seventeen", "eighteen", "nineteen",
                      "twenty",  "a",       "both",      "another",  "first",
                      "second",  "third"};
const int a[27] = {0,  1,  4,  9,  16, 25, 36, 49, 64, 81, 00, 21, 44, 69,
                   96, 25, 56, 89, 24, 61, 0,  1,  4,  1,  1,  4,  9};
int main() {
  int b[6] = {0};
  string str;
  for (int i = 0; i < 6; i++) {
    cin >> str;
    for (int j = 0; j < 27; j++)
      if (str == s[j]) b[i] = a[j];
  }
  sort(b, b + 6);
  ull ans = 0;
  for (int i = 0; i < 6; i++) {
    ans *= 100;
    ans += b[i];
  }
  cout << ans;
  return 0;
}
