#include <bits/stdc++.h>
int var_n[2], cst_n[2], num, k, t = 1;
char var;
int main() {
  std::string str;
  std::cin >> str;
  for (auto c : str) {
    switch (c) {
      case '=':
        var_n[k] += num * t;
        num = 0;
        k = 1;
        t = 1;
        break;
      case '+':
        var_n[k] += num * t;
        num = 0;
        t = 1;
        break;
      case '-':
        var_n[k] += num * t;
        num = 0;
        t = -1;
        break;
    }
    if (isdigit(c)) num = num * 10 + c - '0';
    if (isalpha(c)) {
      if (num == 0) num = 1;
      var = c;
      cst_n[k] += num * t;
      num = 0;
    }
  }
  var_n[1] += num * t;
  if (var_n[0] - var_n[1] == 0) printf("%c=0.000", var);
  else
    printf(
      "%c=%.3lf", var, (double)(var_n[0] - var_n[1]) / (cst_n[1] - cst_n[0]));
  return 0;
  return 0;
}
