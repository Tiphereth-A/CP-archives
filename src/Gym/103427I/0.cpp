#include <bits/stdc++.h>
using namespace std;
using ldb = long double;
using C = complex<ldb>;
ldb eps = 1e-8;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t;
  cin >> t;
  cout << fixed << setprecision(12);
  while (t--) {
    ldb p, q, r, s;
    cin >> p >> q >> r >> s;
    C x1(p, q), w1(r, s);
    cin >> p >> q >> r >> s;
    C x2(p, q), w2(r, s);
    cin >> p >> q >> r >> s;
    C x3(p, q), w3(r, s);
    cin >> p >> q;
    C x0(p, q);
    auto divr = -x1 * (w2 - w3) + x2 * (w1 - w3) - x3 * (w1 - w2);
    if (abs(divr.real()) >= eps || abs(divr.imag()) >= eps) {
      C a, b, d;
      a = -w1 * x1 * (w2 - w3) + w2 * x2 * (w1 - w3) - w3 * x3 * (w1 - w2);
      d = x1 * (w2 * x2 - w3 * x3) - x2 * (w1 * x1 - w3 * x3) +
          x3 * (w1 * x1 - w2 * x2);
      b = x1 * w2 * w3 * (x2 - x3) - x2 * w1 * w3 * (x1 - x3) +
          x3 * w1 * w2 * (x1 - x2);
      a /= divr;
      b /= divr;
      d /= divr;
      C w0 = (a * x0 + b) / (x0 + d);
      cout << w0.real() << ' ' << w0.imag() << '\n';
    } else {
      C a, b;
      divr = x1 - x2;
      a = (w1 - w2) / divr;
      b = (x1 * w2 - x2 * w1) / divr;
      C w0 = a * x0 + b;
      cout << w0.real() << ' ' << w0.imag() << '\n';
    }
  }
}
