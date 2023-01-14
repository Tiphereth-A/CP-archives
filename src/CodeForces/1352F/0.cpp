#include <bits/stdc++.h>
using namespace std;
int main() {
  int kase;
  cin >> kase;
  while (kase--) {
    int n0, n1, n2;
    cin >> n0 >> n1 >> n2;
    string str;
    if (n0) {
      str.append(string(n0 + 1, '0'));
      if (n1) {
        str.push_back('1');
        --n1;
        if (n1 % 2 == 0) {
          for (int i = 0; i < n1; i += 2) str.append("01");
          if (n2) str.append(n2, '1');
        } else {
          for (int i = 2; i < n1; i += 2) str.append("01");
          if (n2) str.append(n2, '1');
          str.push_back('0');
        }
      }
    } else if (n1) {
      if (n2) {
        str = string(n2 + 1, '1');
        if (n1 % 2) {
          str.push_back('0');
          --n1;
          for (int i = 0; i < n1; i += 2) str.append("10");
        } else {
          for (int i = 0; i < n1; i += 2) str.append("01");
        }
      } else if (n1 % 2) {
        for (int i = 0; i < n1; i += 2) str.append("10");
      } else {
        for (int i = 0; i < n1; i += 2) str.append("01");
        str.push_back('0');
      }
    } else if (n2) str = string(n2 + 1, '1');
    cout << str << endl;
  }
  return 0;
}
