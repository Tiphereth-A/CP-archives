#include <bits/stdc++.h>
using namespace std;
bool is_month(int x) { return x > 0 && x <= 12; }
int main() {
  int n, k;
  scanf("%2d%2d", &n, &k);
  int ans = (is_month(n) << 1) + is_month(k);
  switch (ans) {
    case 0: puts("NA"); return 0;
    case 1: puts("YYMM"); return 0;
    case 2: puts("MMYY"); return 0;
    case 3: puts("AMBIGUOUS"); return 0;
  }
}
