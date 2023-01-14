#include <cmath>
#include <cstdio>
const int N = 1005;
struct Complex {
  int re, im;
};
int ans[N];
int main() {
  int kase;
  scanf("%d", &kase);
  while (kase--) {
    Complex x, b;
    scanf("%d%d%d%d", &x.re, &x.im, &b.re, &b.im);
    int len_b = b.re * b.re + b.im * b.im;
    int cnt_ans = 0;
    do {
      bool f = 0;
      for (int a = 0, re, im; a < sqrt(len_b + 1e-8); ++a) {
        re = (x.re - a) * b.re - x.im * (-b.im);
        im = (x.re - a) * (-b.im) + x.im * b.re;
        if (re % len_b == 0 && im % len_b == 0) {
          x.re = re / len_b;
          x.im = im / len_b;
          ans[++cnt_ans] = a;
          f = 1;
          break;
        }
      }
      if (!f || cnt_ans >= 100) break;
    } while (x.re || x.im);
    if (x.re || x.im) puts("The code cannot be decrypted.");
    else {
      printf("%d", ans[cnt_ans]);
      for (int i = cnt_ans - 1; i; --i) printf(",%d", ans[i]);
      puts("");
    }
  }
}
