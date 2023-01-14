#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
const int N = 1e5 + 5;
using namespace std;
struct BigInt {
  int len, n[N];
  BigInt() {
    memset(n, 0, sizeof(n));
    len = 1;
  }
  BigInt operator=(const char *num) {
    len = strlen(num);
    for (int i = 0; i < len; i++) n[i] = num[len - i - 1] - '0';
    return *this;
  }
  BigInt operator=(const int num) {
    char a[N];
    sprintf(a, "%d", num);
    *this = a;
    return *this;
  }
  BigInt(const int num) { *this = num; }
  BigInt(const char *num) { *this = num; }
  BigInt operator+(const BigInt &a) {
    BigInt c;
    c.len = max(len, a.len) + 1;
    for (int i = 0; i < c.len; i++) {
      c.n[i] += n[i] + a.n[i];
      c.n[i + 1] = c.n[i] / 10;
      c.n[i] %= 10;
    }
    if (c.n[c.len - 1] == 0) c.len--;
    return c;
  }
  BigInt operator*(const BigInt &a) {
    BigInt c;
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
ostream &operator<<(ostream &out, const BigInt &x) {
  for (int i = x.len - 1; i >= 0; i--) cout << x.n[i];
  return out;
}
istream &operator>>(istream &in, BigInt &x) {
  char num[N];
  in >> num;
  x = num;
  return in;
}
int main() {
  int n;
  cin >> n;
  for (int cnt = 1; cnt <= n; ++cnt) {
    BigInt a, b;
    cin >> a >> b;
    cout << "Case " << cnt << ":" << endl
         << a << " + " << b << " = " << a + b << endl;
    if (cnt != n) cout << endl;
  }
  return 0;
}
