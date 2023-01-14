#include <iostream>
#include <string>
using namespace std;
string s;
int idx, h1, h2;
void solve(int dep1, int dep2) {
  int _ = 0;
  while (s[idx] == 'd') {
    ++idx;
    ++_;
    solve(dep1 + 1, dep2 + _);
  }
  dep1 > h1 ? h1 = dep1 : h1;
  dep2 > h2 ? h2 = dep2 : h2;
  ++idx;
}
int main() {
  int kase = 0;
  while (cin >> s && s != "#") {
    idx = h1 = h2 = 0;
    solve(0, 0);
    cout << "Tree " << ++kase << ": " << h1 << " => " << h2 << endl;
  }
  return 0;
}
