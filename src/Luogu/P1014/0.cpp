#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, k = 0, s = 0;
  cin >> n;
  while (s < n) {
    k++;
    s += k;
  }
  if (k % 2 == 0) {
    printf("%d/%d", k - s + n, s - n + 1);
  } else {
    printf("%d/%d", s - n + 1, k - s + n);
  }
  return 0;
}
