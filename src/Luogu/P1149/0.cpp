#include <bits/stdc++.h>
using std::cin;
using std::cout;
const int match[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6}, N = 1111;
int solve(int num) {
  int sum = 0;
  while (num / 10) {
    sum += match[num % 10];
    num /= 10;
  };
  sum += match[num];
  return sum;
}
int main() {
  int n;
  cin >> n;
  n -= 4;
  int sum = 0;
  for (int a = 0; a <= N; ++a) {
    for (int b = 0; b <= N; ++b) {
      if (solve(a) + solve(b) + solve(a + b) == n) sum++;
    }
  }
  cout << sum;
  return 0;
}
