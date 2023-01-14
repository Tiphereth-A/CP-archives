#include <bits/stdc++.h>
using namespace std;
bool prime(int n) {
  int i = 2;
  while (i <= sqrt(n))
    if (!(n % i++)) return false;
  return true;
}
int main() {
  int n;
  cin >> n;
  for (int i = 2; i <= 20000; i++)
    for (int j = i; n - i - j >= j; j++)
      if (prime(i) && prime(j) && prime(n - i - j))
        return !printf("%d %d %d\n", i, j, n - i - j);
}
