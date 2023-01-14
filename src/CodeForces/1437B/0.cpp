#include <bits/stdc++.h>
using namespace std;
int main() {
  int kase;
  cin >> kase;
  while (kase--) {
    int n;
    string str;
    cin >> n >> str;
    int cnt = 0, ans = 0;
    char now = str[0];
    for (char ch : str) {
      if (now == ch) ++cnt;
      else {
        ans += cnt - 1;
        cnt = 1;
        now = ch;
      }
    }
    ans += cnt - 1;
    cout << (ans + 1) / 2 << endl;
  __end_kase:;
  }
  return 0;
}
