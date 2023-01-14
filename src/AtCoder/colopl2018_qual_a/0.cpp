#include <iostream>
#include <string>
using namespace std;
string str;
int a, b;
int main() {
  cin >> a >> b >> str;
  if (str.size() >= a && str.size() <= b) cout << "YES" << endl;
  else cout << "NO" << endl;
  return 0;
}
