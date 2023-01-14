#include <bits/stdc++.h>
using namespace std;
int main() {
  int kase;
  scanf("%d", &kase);
  while (kase--) {
    int x;
    scanf("%d", &x);
    puts(x % 4 ? "October wins!" : "Roy wins!");
  }
}
