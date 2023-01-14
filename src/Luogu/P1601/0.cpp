#include <bits/stdc++.h>
#define MAXN 10000
using namespace std;
struct f {
  int len, n[MAXN];
  f() {
    memset(n, 0, sizeof(n));
    len = 1;
  }
  f operator=(const char *num) {
    len = strlen(num);
    for (int i = 0; i < len; i++) n[i] = num[len - i - 1] - '0';
    return *this;
  }
  f operator=(const int num) {
    char a[MAXN];
    sprintf(a, "%d", num);
    *this = a;
    return *this;
  }
  f(const int num) { *this = num; }
  f(const char *num) { *this = num; }
  f operator+(const f &a) {
    f c;
    c.len = max(len, a.len) + 1;
    for (int i = 0; i < c.len; i++) {
      c.n[i] += n[i] + a.n[i];
      c.n[i + 1] = c.n[i] / 10;
      c.n[i] %= 10;
    }
    if (c.n[c.len - 1] == 0) c.len--;
    return c;
  }
  f operator*(const f &a) {
    f c;
    c.len = len + a.len;
    for (int i = 0; i < len; i++)
      for (int j = 0; j < a.len; j++) {
        c.n[i + j] += n[i] * a.n[j];
        c.n[i + j + 1] += c.n[i + j] / 10;
        c.n[i + j] %= 10;
      }
    if (c.n[c.len - 1] == 0) c.len--;
    return c;
  }
};
ostream &operator<<(ostream &out, const f &x) {
  for (int i = x.len - 1; i >= 0; i--) cout << x.n[i];
  return out;
}
istream &operator>>(istream &in, f &x) {
  char num[MAXN];
  in >> num;
  x = num;
  return in;
}
int main() {
  f a, b;
  cin >> a >> b;
  f c;
  c = a + b;
  cout << c;
  return 0;
}
