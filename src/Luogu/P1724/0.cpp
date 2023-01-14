#include <bits/stdc++.h>
using namespace std;
struct {
  long long x, y;
} p[5010];
int main() {
  string s;
  cin >> s;
  long long t;
  cin >> t;
  for (int i = 1; i <= s.length(); i++) {
    switch (s[i - 1]) {
      case 'E':
        p[i % s.length()].x = p[i - 1].x + 1;
        p[i % s.length()].y = p[i - 1].y;
        break;
      case 'S':
        p[i % s.length()].x = p[i - 1].x;
        p[i % s.length()].y = p[i - 1].y - 1;
        break;
      case 'W':
        p[i % s.length()].x = p[i - 1].x - 1;
        p[i % s.length()].y = p[i - 1].y;
        break;
      case 'N':
        p[i % s.length()].x = p[i - 1].x;
        p[i % s.length()].y = p[i - 1].y + 1;
        break;
      default: break;
    }
  }
  long long d = t / s.length();
  t %= s.length();
  long long xx = d * p[0].x, yy = d * p[0].y;
  if (t) {
    xx += p[t].x;
    yy += p[t].y;
  }
  cout << xx << ' ' << yy;
  return 0;
}
