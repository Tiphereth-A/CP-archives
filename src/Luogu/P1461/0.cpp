#include <bits/stdc++.h>
using namespace std;
int n, b, d, ans[75], len;
int main() {
  scanf("%d%d%d", &n, &b, &d);
  len++;
  ans[len] = 0;
  int i = 1;
  while (len < n) {
    bool flag = false;
    for (int j = len; j >= 1; j--)
      if (__builtin_popcount(ans[j] ^ i) < d) {
        flag = true;
        break;
      }
    if (!flag) {
      len++;
      ans[len] = i;
    }
    i++;
  }
  for (i = 1; i <= len; i++) {
    printf("%d ", ans[i]);
    if (i % 10 == 0) cout << endl;
  }
  return 0;
}
