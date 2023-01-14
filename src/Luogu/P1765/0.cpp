#include <bits/stdc++.h>
const int k[26] = {1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1,
                   2, 3, 1, 2, 3, 4, 1, 2, 3, 1, 2, 3, 4};
using namespace std;
int main() {
  int ans = 0;
  char c;
  while ((c = getchar()) != '\n') {
    if (c == ' ') ans++;
    else if (c >= 'a' && c <= 'z') ans += k[c - 'a'];
  }
  cout << ans;
  return 0;
}
