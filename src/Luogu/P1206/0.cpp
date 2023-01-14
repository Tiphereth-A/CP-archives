#include <bits/stdc++.h>
using namespace std;
char c(int x) {
  if (x >= 0 && x <= 9) return x + '0';
  return x + 55;
}
int b;
struct Node {
  int l, a[20];
  Node(int x) {
    for (l = 0; x; l++) {
      a[l] = x % b;
      x /= b;
    }
  }
  void out() {
    for (int i = l - 1; i >= 0; i--) printf("%c", c(a[i]));
  }
  bool tf() {
    for (int i = 0; i < l; i++)
      if (a[i] != a[l - i - 1]) return false;
    return true;
  }
};
int main() {
  scanf("%d", &b);
  for (int i = 1; i <= 300; i++) {
    Node n(i * i);
    if (n.tf()) {
      Node(i).out();
      putchar(' ');
      n.out();
      putchar('\n');
    }
  }
  return 0;
}
