#include <iostream>
#include <string>
using namespace std;
string s;
int l;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> s;
  l = s.size();
  for (int i = 0; i < l; i++) {
    if (s[i] == 'C') {
      for (int j = i + 1; j < l; j++) {
        if (s[j] == 'F') {
          cout << "Yes" << endl;
          return 0;
        }
      }
    }
  }
  cout << "No" << endl;
  return 0;
}
