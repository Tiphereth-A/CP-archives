#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, k;
  cin >> n >> k;
  int stair[100010] = {0};
  stair[0] = 1;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= k && (i - j) >= 0; j++) {
      stair[i] += stair[i - j];
      stair[i] %= 100003;
    }
  cout << stair[n];
  return 0;
}
