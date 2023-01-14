#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  string str;
  cin >> n >> str;
  while (n--) {
    int a, b, c;
    string s;
    cin >> a;
    switch (a) {
      case 1:
        cin >> s;
        cout << (str += s) << endl;
        break;
      case 2:
        cin >> b >> c;
        cout << (str = str.substr(b, c)) << endl;
        break;
      case 3:
        cin >> b >> s;
        str.insert(b, s);
        cout << str << endl;
        break;
      case 4: cin >> s; cout << (int)str.find(s) << endl;
    }
  }
}
