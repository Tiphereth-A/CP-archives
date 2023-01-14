#include <bits/stdc++.h>
using namespace std;
#define _for(i, l, r) for (decltype(l + r) i = (l); i <= (r); ++i)
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int kase;
  cin >> kase;
  while (kase--) {
    string str;
    cin >> str;
    bool flag = 0;
    _for(i, 1, 6) {
      bool a = i & 1, b = i & 2, c = i & 4;
      int cnt = 0;
      for (char ch : str) {
        ((a && ch == 'A') || (b && ch == 'B') || (c && ch == 'C')) ? ++cnt :
                                                                     --cnt;
        if (cnt < 0) break;
      }
      flag |= cnt == 0;
    }
    cout << (flag ? "YES" : "NO") << '\n';
  }
  return 0;
}
