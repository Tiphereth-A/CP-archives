#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
int a[100005];
const char map[] = "2223334445556667 77888999 ";
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    string s;
    cin >> s;
    for (int j = 0; j < s.length(); ++j) {
      if (s[j] == 'Q' || s[j] == 'Z' || s[j] == '-') continue;
      if (isupper(s[j])) s[j] = map[s[j] - 'A'];
    }
    for (int j = s.length() - 1, m = 1; j >= 0; j--)
      if (s[j] == '-' || s[j] == 'Q' || s[j] == 'Z') continue;
      else {
        a[i] += (s[j] - '0') * m;
        m *= 10;
      }
  }
  sort(a + 1, a + n + 1);
  bool f = true;
  for (int i = 2, t = 0, cnt = 1; i <= n + 1; ++i)
    if (i <= n && a[i] == a[i - 1]) {
      t = a[i];
      ++cnt;
    } else {
      if (cnt >= 2) {
        int t1 = a[i - 1] / 10000;
        cout << t1 / 100 << (t1 - t1 / 100 * 100) / 10 << t1 % 10 << "-";
        t1 = a[i - 1] % 10000;
        cout << t1 / 1000;
        t1 -= t1 / 1000 * 1000;
        cout << t1 / 100;
        t1 -= t1 / 100 * 100;
        cout << t1 / 10 << t1 % 10 << " " << cnt << endl;
        f = 0;
      }
      cnt = 1;
    }
  if (f) cout << "No duplicates.";
  return 0;
}
