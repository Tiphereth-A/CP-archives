#include <bits/stdc++.h>
using namespace std;
int main() {
  int kase;
  cin >> kase;
  while (kase--) {
    string str;
    cin >> str;
    sort(str.begin(), str.end());
    cout << str << endl;
    while (next_permutation(str.begin(), str.end())) cout << str << endl;
    cout << endl;
  }
  return 0;
}
