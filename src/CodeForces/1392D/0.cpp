#include <bits/stdc++.h>
using namespace std;
int main() {
#define __(i) \
  s[(i) >= n ? (i) - n : (i) + n] = s[(i)] = (s[(i)] == 'R' ? 'L' : 'R')
  int kase;
  cin >> kase;
  while (kase--) {
    int n;
    string s;
    cin >> n >> s;
    s += s;
    char now = 0;
    int cnt = 0, ans = 0;
    int st = 0;
    while (st < n && s[st] == s[st + 1]) ++st;
    if (st == n) st = 0;
    for (int i = st; i < s.size(); ++i) {
      if (s[i] != now) {
        now = s[i];
        cnt = 1;
        continue;
      }
      if (++cnt == 3) {
        if (s[i] == s[i + 1]) __(i);
        else __(i - 1);
        now = s[i];
        cnt = 1;
        ++ans;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
