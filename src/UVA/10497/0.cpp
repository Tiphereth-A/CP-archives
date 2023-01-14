#include <cstring>
#include <iostream>
#include <string>
using namespace std;
const int N = 2e4 + 10;
struct BigInt {
  int len, s[N];
  BigInt() {
    memset(s, 0, sizeof(s));
    len = 1;
  }
  BigInt(int num) { *this = num; }
  BigInt(const char *num) { *this = num; }
  BigInt operator=(int num) {
    char s[N];
    sprintf(s, "%d", num);
    *this = s;
    return *this;
  }
  string str() const {
    string res = "";
    for (int i = 0; i < len; i++) res = (char)(s[i] + '0') + res;
    if (res == "") res = "0";
    return res;
  }
  void clean() {
    while (len > 1 && !s[len - 1]) len--;
  }
  BigInt operator=(const char *num) {
    len = strlen(num);
    for (int i = 0; i < len; i++) s[i] = num[len - i - 1] - '0';
    return *this;
  }
  BigInt operator+(const BigInt &b) const {
    BigInt c;
    c.len = 0;
    for (int i = 0, g = 0; g || i < max(len, b.len); i++) {
      int x = g;
      if (i < len) x += s[i];
      if (i < b.len) x += b.s[i];
      c.s[c.len++] = x % 10;
      g = x / 10;
    }
    return c;
  }
  BigInt operator*(const BigInt &b) {
    BigInt c;
    c.len = len + b.len;
    for (int i = 0; i < len; i++)
      for (int j = 0; j < b.len; j++) c.s[i + j] += s[i] * b.s[j];
    for (int i = 0; i < c.len - 1; i++) {
      c.s[i + 1] += c.s[i] / 10;
      c.s[i] %= 10;
    }
    c.clean();
    return c;
  }
  BigInt operator-(const BigInt &b) {
    BigInt c;
    c.len = 0;
    for (int i = 0, g = 0; i < len; i++) {
      int x = s[i] - g;
      if (i < b.len) x -= b.s[i];
      if (x >= 0) g = 0;
      else {
        g = 1;
        x += 10;
      }
      c.s[c.len++] = x;
    }
    c.clean();
    return c;
  }
};
ostream &operator<<(ostream &out, const BigInt &x) {
  out << x.str();
  return out;
}
BigInt ans[805];
int main() {
  int n;
  ans[1] = 0;
  ans[2] = 1;
  for (int i = 3; i <= 800; ++i)
    ans[i] = BigInt(i - 1) * (ans[i - 1] + ans[i - 2]);
  while (cin >> n && ~n) cout << ans[n] << endl;
  return 0;
}
