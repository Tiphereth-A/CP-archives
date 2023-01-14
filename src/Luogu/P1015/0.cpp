#include <bits/stdc++.h>
#define M 100005
#define _for(i, l, r) for (int i = (l); i <= (r); i++)
#define max(a, b) (((a) > (b)) ? (a) : (b))
using namespace std;
struct num {
  int n[M];
} s1;
int ans, m;
void scan(num &a) {
  a.n[0] = 0;
  char c = getchar();
  if (isalpha(c)) c = toupper(c);
  while ((c < '0' || c > '9') && (c < 'A' || c > 'F')) { c = getchar(); }
  while ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F')) {
    ++a.n[0];
    if (isalpha(c)) a.n[a.n[0]] = c - 55;
    else a.n[a.n[0]] = c - 48;
    c = getchar();
    if (isalpha(c)) c = toupper(c);
  }
}
num rev(num &a) {
  num x;
  x.n[0] = a.n[0];
  _for(i, 1, a.n[0]) x.n[i] = a.n[a.n[0] - i + 1];
  return x;
}
void nplus(num &a, num b) {
  int s = max(a.n[0], b.n[0]), c = 0;
  a.n[0] = s;
  _for(i, 1, s) {
    a.n[i] += b.n[i] + c;
    c = a.n[i] / m;
    a.n[i] %= m;
    if (c && i == s) {
      ++s;
      ++a.n[0];
    }
  }
}
bool f(num a) {
  int c = a.n[0] / 2;
  _for(i, 1, c)
    if (a.n[i] != a.n[a.n[0] - i + 1]) return true;
  return false;
}
int main() {
  scanf("%d", &m);
  scan(s1);
  while (f(s1)) {
    nplus(s1, rev(s1));
    ans++;
    if (ans > 30) {
      cout << "Impossible!";
      return 0;
    }
  }
  cout << "STEP=" << ans;
  return 0;
}
