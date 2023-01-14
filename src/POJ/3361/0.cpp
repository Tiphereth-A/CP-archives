#include <cmath>
#include <cstdio>
#include <queue>
using std::priority_queue;
struct Complex {
  int re, im;
  Complex(int a = 0, int b = 0): re(a), im(b) {}
  bool operator<(const Complex &rhs) const {
    return re == rhs.re ? im > rhs.im : re > rhs.re;
  }
};
int main() {
  int n, kase = 0;
  while (~scanf("%d", &n)) {
    ++kase;
    if (n == 1) {
      printf("Case #%d:\n", kase);
      continue;
    }
    priority_queue<Complex> q;
    for (int i = 2; i <= n; ++i)
      if (n % i == 0) {
        while (n % i == 0) n /= i;
        if (i % 4 == 3) q.push(Complex(i));
        else
          for (int a = 1; a * a < i; ++a)
            for (int b = 1; a * a + b * b <= i; ++b)
              if (a * a + b * b == i) {
                q.push(Complex(a, b));
                goto _end;
              }
      _end:;
      }
    printf("Case #%d:", kase);
    while (!q.empty()) {
      Complex now = q.top();
      q.pop();
      printf(" %d", now.re);
      if (now.im == 1) printf("+j, %d-j", now.re);
      else if (now.im) printf("+%dj, %d-%dj", now.im, now.re, now.im);
      putchar(q.empty() ? '\n' : ',');
    }
  }
}
