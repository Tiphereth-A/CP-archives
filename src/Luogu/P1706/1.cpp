#include <bits/stdc++.h>
#define _for(i, l, r) for (int i = (l); i <= (r); ++i)
int x[30], n;
int main() {
  scanf("%d", &n);
  _for(i, 1, n) {
    x[i] = i;
    printf("%5.d", i);
  }
  while (std::next_permutation(x + 1, x + 1 + n)) {
    puts("");
    _for(i, 1, n) printf("%5.d", x[i]);
  }
}
