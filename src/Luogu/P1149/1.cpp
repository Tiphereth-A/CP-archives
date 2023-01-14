#include <bits/stdc++.h>
using namespace std;
const int match[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
int m(int num) {
  int n = num, sum = 0;
  while (n / 10) {
    sum += match[n % 10];
    n /= 10;
  };
  sum += match[n];
  return sum;
}
int main() {
  int n;
  cin >> n;
  n -= 4;
  int a, b, c, sum = 0;
  for (a = 0; a <= 1111; a++) {
    for (b = 0; b <= 1111; b++) {
      c = a + b;
      if (m(a) + m(b) + m(c) == n) sum++;
    }
  }
  cout << sum;
  return 0;
}
