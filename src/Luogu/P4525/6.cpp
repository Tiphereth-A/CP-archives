#include <bits/stdc++.h>
using namespace std;
class Romberg {
protected:
  function<long double(long double)> f;
  long double ctqf(long double a, long double b, long double h) {
    static long double ans;
    ans = 0.0;
    for (long double i = a + h / 2.0; i < b; i += h) ans += f(i);
    return ans;
  }

public:
#define continue \
  {              \
    k++;         \
    continue;    \
  }
  Romberg(function<long double(long double)> F = [](long double x) {
    return x;
  }) {
    f = F;
  }
  long double operator()(long double a, long double b, long double eps) {
    static long double T1, T2, S1, S2, C1, C2, R1, R2, h, S;
    static int cnt, k;
    h = b - a, T1 = (f(a) + f(b)) * h / 2, cnt = 0, k = 1;
    while (1) {
      S = ctqf(a, b, h), T2 = (T1 + h * S) / 2, S2 = (4 * T2 - T1) / 3, h /= 2,
      T1 = T2, S1 = S2, C1 = C2, R1 = R2, cnt++;
      if (k == 1) continue;
      C2 = (16 * S2 - S1) / 15;
      if (k == 2) continue;
      R2 = (64 * C2 - C1) / 63;
      if (k == 3) continue;
      if (fabs(R1 - R2) < eps || cnt > 100) break;
    }
    return R2;
  }
#undef continue
};
int main() {
  long double a, b, c, d, l, r;
  cin >> a >> b >> c >> d >> l >> r;
  printf("%.6Lf\n", Romberg([a, b, c, d](long double x) {
           return (c * x + d) / (a * x + b);
         })(l, r, 1e-8));
}
