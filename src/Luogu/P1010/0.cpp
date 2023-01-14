#include <bits/stdc++.h>
using namespace std;
void p(int n) {
  int i;
  int flag = 0;
  switch (n) {
    case 0: printf("2(0)"); break;
    case 1: printf("2"); break;
    default:
      for (i = 14; i >= 0; i--)
        if (n & (1 << i)) {
          if (flag) printf("+");
          else flag++;
          if (i != 1 && i != 0) {
            printf("2(");
            p(i);
            printf(")");
          } else p(i);
        }
      break;
  }
  return;
}
int main() {
  int n;
  scanf("%d", &n);
  p(n);
  return 0;
}
