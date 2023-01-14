#include <bits/stdc++.h>
using namespace std;
bool ok(char x) {
  x = tolower(x);
  if (x == 'a' || x == 'e' || x == 'i' || x == 'o' || x == 'u') return 1;
  return 0;
}
int main() {
  string str;
  while (getline(cin, str)) {
    int i = 0, len = str.size();
    while (i < len)
      if (isalpha(str[i])) {
        bool f = 1;
        char ch;
        if (ok(str[i])) f = 0;
        else ch = str[i++];
        while (isalpha(str[i])) cout << str[i++];
        if (f) cout << ch;
        cout << "ay";
      } else cout << str[i++];
    cout << endl;
  }
  return 0;
}
