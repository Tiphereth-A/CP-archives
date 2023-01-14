#include <iostream>
#include <map>
#include <sstream>
#include <string>
using namespace std;
map<string, string> mp;
string a, b, c;
int main() {
  while (getline(cin, a) && a[0]) {
    istringstream ss(a);
    ss >> b >> c;
    mp[c] = b;
  }
  while (getline(cin, a))
    if (mp.find(a) != mp.end()) cout << mp[a] << endl;
    else cout << "eh" << endl;
}
