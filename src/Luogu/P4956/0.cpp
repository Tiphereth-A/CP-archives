#include <bits/stdc++.h>
using namespace std;
int main() {
  int n;
  scanf("%d", &n);
  n /= 364;
  if (n <= 103) printf("%d\n%d\n", n - 3, 1);
  else {
    printf("%d\n%d\n",
           99 + (n % 3 == 1 ? 1 :
                 n % 3      ? -1 :
                              0),
           (n - 99 -
            (n % 3 == 1 ? 1 :
             n % 3      ? -1 :
                          0)) /
             3);
  }
}
