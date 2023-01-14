#include <bits/stdc++.h>
using std::cin;
using std::cout;
const int frac[] = {0, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
int num[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int n;
int main() {
  cin >> n;
  for (int i = 1; i <= frac[n]; ++i) {
    for (int j = 1; j <= n; ++j) printf("%5d", num[j]);
    puts("");
    std::next_permutation(num + 1, num + n + 1);
  }
  return 0;
}
