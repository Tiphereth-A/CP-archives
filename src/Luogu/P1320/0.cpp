#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
std::string s;
int n, cnt = 0;
bool cur = 0;
int main() {
  cin >> s;
  n = s.size();
  cout << n << ' ';
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < n; ++j) {
      if ((s[j] - '0') == cur) ++cnt;
      else {
        cout << cnt << ' ';
        cnt = 1;
        cur = !cur;
      }
    }
    cin >> s;
  }
  cout << cnt << endl;
  return 0;
}
