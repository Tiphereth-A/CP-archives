#include <cstdlib>
#include <iostream>
using namespace std;
bool solve(int *exp) {
  char s[30];
  cin >> s;
  if (s[0] == 'E') return false;
  else if (s[0] == 'B')
    while (solve(exp));
  else if (s[0] == 'O') {
    cin >> s;
    exp[0] += atoi(s);
    return solve(exp);
  } else {
    int _[11] = {0};
    cin >> s;
    while (solve(_));
    if (s[0] == 'n') {
      for (int i = 10; i > 0; --i) _[i] = _[i - 1];
      _[0] = 0;
    } else {
      int x = atoi(s);
      for (int i = 0; i < 11; ++i) _[i] *= x;
    }
    for (int i = 0; i < 11; ++i) exp[i] += _[i];
  }
  return true;
}
int main() {
  int kase;
  cin >> kase;
  for (int cnt = 1; cnt <= kase; ++cnt) {
    char s[6];
    int exp[11] = {0};
    solve(exp);
    cout << "Program #" << cnt << endl << "Runtime = ";
    bool f = false, before = false;
    for (int i = 10; i >= 0; --i)
      if (exp[i]) {
        f = true;
        if (before) {
          cout << '+';
          before = false;
        }
        if (!i) {
          cout << exp[i];
          before = false;
        } else {
          bool f = false;
          if (i && exp[i] != 1) {
            f = true;
            cout << exp[i];
            before = true;
          }
          if (i) {
            if (f) cout << '*';
            cout << 'n';
            if (i != 1) cout << '^' << i;
            before = true;
          }
        }
      }
    if (!f) cout << 0;
    cout << endl << endl;
  }
  return 0;
}
