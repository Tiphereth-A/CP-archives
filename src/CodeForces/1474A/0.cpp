#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int kase;
  cin >> kase;
  while (kase--) {
    int n;
    cin >> n;
    string a, b;
    cin >> b;
    char pre = '0', now;
    for (char ch : b) {
      if (ch == '0') {
        now = (pre == '1' ? '0' : '1');
        pre = (now == '0' ? '0' : '1');
      } else {
        now = (pre == '2' ? '0' : '1');
        pre = (now == '0' ? '1' : '2');
      }
      a.push_back(now);
    }
    cout << a << '\n';
  }
  return 0;
}
