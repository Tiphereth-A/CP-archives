#include <iostream>
#include <string>
using namespace std;
string s;
int ans, cnt, n;
int main() {
  cin >> n;
  while (n--) {
    cin >> s;
    ans = cnt = 0;
    int len = s.size();
    for (int i = 0; i < len; ++i) {
      if (s[i] == 'X') continue;
      else if (i) {
        if (s[i] == s[i - 1]) ans += ++cnt;
        else ans += (cnt = 1);
      } else {
        cnt = 1;
        ++ans;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
