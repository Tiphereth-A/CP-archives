#include <bits/stdc++.h>
using namespace std;
int a[10000][2];
int main() {
  char c;
  int i = 0, w1 = 0, l1 = 0, w2 = 0, l2 = 0;
  while (scanf("%c", &c) && c != 'E') {
    if (c == 'W') {
      w1++;
      w2++;
    }
    if (c == 'L') {
      l1++;
      l2++;
    }
    if ((w1 >= 11 && w1 - l1 >= 2) || (l1 >= 11 && l1 - w1 >= 2)) {
      printf("%d:%d\n", w1, l1);
      w1 = 0;
      l1 = 0;
    };
    if ((w2 >= 21 && w2 - l2 >= 2) || (l2 >= 21 && l2 - w2 >= 2)) {
      a[i][0] = w2;
      a[i][1] = l2;
      i++;
      w2 = 0;
      l2 = 0;
    };
  }
  printf("%d:%d\n\n", w1, l1);
  for (int j = 0; j < i; j++) printf("%d:%d\n", a[j][0], a[j][1]);
  printf("%d:%d\n", w2, l2);
  return 0;
}
