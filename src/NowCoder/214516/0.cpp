#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
struct {
  char ch;
  int num;
  operator int() { return num; }
} a[N];
int cnt_a;
int main() {
  int n;
  string s;
  cin >> n >> s;
  char now_ch = s[0];
  int now = 0;
  for (char ch : s) {
    if (now_ch == ch) ++now;
    else {
      a[++cnt_a] = {now_ch, now};
      now_ch = ch;
      now = 1;
    }
  }
  if (now) a[++cnt_a] = {now_ch, now};
  int ans = 0;
  if (a[1].ch == 'A') {
    ans = a[1] + a[2];
    for (int i = 3; i <= n; i += 2) ans = max(ans, a[i] + a[i + 1]);
    now = a[1] + a[2] + a[3] + a[4];
    for (int i = 3; i <= cnt_a; i += 2) {
      now = max(now, a[i] + a[i + 1] + a[i + 2] + a[i + 3]);
    }
  } else {
    ans = a[1];
    for (int i = 2; i <= n; i += 2) ans = max(ans, a[i] + a[i + 1]);
    now = a[2] + a[3] + a[4] + a[5];
    for (int i = 4; i <= cnt_a; i += 2) {
      now = max(now, a[i] + a[i + 1] + a[i + 2] + a[i + 3]);
    }
    now = max(now, a[1] + a[2] + a[3]);
  }
  cout << max(ans, now);
  return 0;
}
