#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
int main() {
  string str;
  while (getline(cin, str) && str[0] != '#') {
    if (!next_permutation(str.begin(), str.end()))
      cout << "No Successor" << endl;
    else cout << str << endl;
  }
}
