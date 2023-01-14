#include <cstdio>
#define _(x, a, b)      \
  {                     \
    if ((b) > 1) {      \
      (x) += (a) / (b); \
      (a) %= (b);       \
    } else {            \
      (x) += (a) - 1;   \
      (a) = 1;          \
    }                   \
  }
int main() {
  int kase;
  scanf("%d", &kase);
  for (int cnt = 1; cnt <= kase; ++cnt) {
    int a, b;
    scanf("%d%d", &a, &b);
    int l = 0, r = 0;
    while ((a > 1 || b > 1) && a != b)
      if (a > b) _(l, a, b)
      else _(r, b, a);
    printf(
      "Scenario #%d:\n"
      "%d %d\n%s",
      cnt,
      l,
      r,
      (cnt == kase ? "" : "\n"));
  }
}
