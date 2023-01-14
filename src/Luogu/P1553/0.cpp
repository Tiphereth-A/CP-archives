#include <bits/stdc++.h>
using std::cin;
using std::cout;
std::string s;
char p;
int cnt;
int main() {
  cin >> s;
  int len = s.size();
  for (auto c : s) {
    if (isdigit(c)) ++cnt;
    else {
      p = c;
      break;
    }
  }
  int x = cnt--;
  while (s[cnt] == '0' && cnt) --cnt;
  for (int i = cnt; i + 1; --i) cout << s[i];
  if (p == 0) return 0;
  else if (p == '%') {
    cout << p;
    return 0;
  } else cout << p;
  --len;
  while (s[x + 1] == '0' && x < len - 1) ++x;
  while (s[len] == '0' && len > x + 1) --len;
  for (int i = len; i > x; --i) cout << s[i];
  return 0;
}
