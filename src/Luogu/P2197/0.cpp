#include <bits/stdc++.h>
int main() {
  int t, n;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    int ans = 0, tmp;
    while (n--) {
      scanf("%d", &tmp);
      ans ^= tmp;
    }
    puts(ans ? "Yes" : "No");
  }
}
