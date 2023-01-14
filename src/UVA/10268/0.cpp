#include <cctype>
#include <cstdio>
using namespace std;
int main() {
  int x, a, _;
  while (~scanf("%d%*c", &x)) {
    _ = getchar();
    int sum = 0, ans = 0;
    while (_ != '\n' && ~_) {
      if (_ == '-' || isdigit(_)) {
        ungetc(_, stdin);
        scanf("%d", &a);
        ans = ans * x + sum;
        sum = sum * x + a;
      }
      _ = getchar();
    }
    printf("%d\n", ans);
  }
  return 0;
}
