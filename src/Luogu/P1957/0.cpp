#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  cin >> n;
  char ch;
  while (n--) {
    string s;
    stringstream ss;
    int a, b;
    if (!(cin >> a)) {
      cin.clear();
      cin >> ch >> a;
    }
    cin >> b;
    ss << a
       << (ch == 'a' ? '+' :
           ch == 'b' ? '-' :
                       '*')
       << b << '='
       << (ch == 'a' ? a + b :
           ch == 'b' ? a - b :
                       a * b);
    ss >> s;
    cout << s << endl << s.size() << endl;
  }
}
